from typing import Optional, List, Dict, Any, Tuple
from datetime import datetime

# 修正导入：绝对导入
from infra.redis_store import get_redis, atomic_create_with_uniques, TxnError
from domain.entities import (
    User, Patient, Doctor, Appointment, MedicalRecord, Prescription, Attendance, ChatMessage
)

r = get_redis()

# Key schema 约定（与之前一致）
class UserRepo:
    id_counter = "next_user_id"

    @staticmethod
    def key_user(uid: int) -> str: return f"user:{uid}"
    @staticmethod
    def key_username(name: str) -> str: return f"username:{name}"

    def create_user(self, username: str, password_hash: str, role: str) -> Tuple[Optional[int], Optional[str]]:
        now = datetime.utcnow().isoformat()
        try:
            new_id = atomic_create_with_uniques(
                r=r,
                id_counter_key=self.id_counter,
                unique_checks=((self.key_username(username), ""),),
                write_hash_key_fn=lambda nid: self.key_user(nid),
                write_hash_mapping={
                    "username": username,
                    "password_hash": password_hash,
                    "role": role,
                    "created_at": now,
                },
                set_unique_index_fns=(lambda nid: (self.key_username(username), nid),)
            )
            return new_id, None
        except TxnError as e:
            return None, str(e)

    def get_by_id(self, uid: int) -> Optional[User]:
        h = r.hgetall(self.key_user(uid))
        if not h: return None
        return User.from_hash(uid, h)

    def get_by_username(self, username: str) -> Optional[User]:
        uid = r.get(self.key_username(username))
        if not uid: return None
        return self.get_by_id(int(uid))

    def update_password_hash(self, uid: int, new_hash: str) -> bool:
        return r.hset(self.key_user(uid), "password_hash", new_hash) is not None

class PatientRepo:
    id_counter = "next_patient_id"

    @staticmethod
    def key_patient(pid: int) -> str: return f"patient:{pid}"
    @staticmethod
    def key_patient_by_user(uid: int) -> str: return f"patient:user:{uid}"
    @staticmethod
    def key_by_idcard(idcard: str) -> str: return f"patient:idcard:{idcard}"

    def create_patient(self, user_id: int, name: str, gender: str, id_card_number: str, phone: str, email: str) -> Tuple[Optional[int], Optional[str]]:
        now = datetime.utcnow().isoformat()
        try:
            new_id = atomic_create_with_uniques(
                r=r,
                id_counter_key=self.id_counter,
                unique_checks=((self.key_by_idcard(id_card_number), ""),),
                write_hash_key_fn=lambda nid: self.key_patient(nid),
                write_hash_mapping={
                    "user_id": user_id,
                    "name": name,
                    "gender": gender,
                    "id_card_number": id_card_number,
                    "phone_number": phone,
                    "email": email,
                    "created_at": now,
                },
                set_unique_index_fns=(
                    lambda nid: (self.key_by_idcard(id_card_number), nid),
                    lambda nid: (self.key_patient_by_user(user_id), nid),
                )
            )
            return new_id, None
        except TxnError as e:
            return None, str(e)

    def get_by_id(self, pid: int) -> Optional[Patient]:
        h = r.hgetall(self.key_patient(pid))
        if not h: return None
        return Patient.from_hash(pid, h)

    def get_by_user_id(self, uid: int) -> Optional[Patient]:
        pid = r.get(self.key_patient_by_user(uid))
        if not pid: return None
        return self.get_by_id(int(pid))

class DoctorRepo:
    id_counter = "next_doctor_id"

    @staticmethod
    def key_doctor(did: int) -> str: return f"doctor:{did}"
    @staticmethod
    def key_doctor_by_user(uid: int) -> str: return f"doctor:user:{uid}"
    @staticmethod
    def key_by_workid(workid: str) -> str: return f"doctor:workid:{workid}"

    def create_doctor(self, user_id: int, work_id: str, name: str, department: str,
                      personal_profile: str, photo_url: str, consultation_fee: str) -> Tuple[Optional[int], Optional[str]]:
        now = datetime.utcnow().isoformat()
        try:
            new_id = atomic_create_with_uniques(
                r=r,
                id_counter_key=self.id_counter,
                unique_checks=((self.key_by_workid(work_id), ""),),
                write_hash_key_fn=lambda nid: self.key_doctor(nid),
                write_hash_mapping={
                    "user_id": user_id,
                    "work_id": work_id,
                    "name": name,
                    "department": department,
                    "personal_profile": personal_profile,
                    "photo_url": photo_url,
                    "consultation_fee": consultation_fee,
                    "created_at": now,
                },
                set_unique_index_fns=(
                    lambda nid: (self.key_by_workid(work_id), nid),
                    lambda nid: (self.key_doctor_by_user(user_id), nid),
                )
            )
            return new_id, None
        except TxnError as e:
            return None, str(e)

    def get_by_id(self, did: int) -> Optional[Doctor]:
        h = r.hgetall(self.key_doctor(did))
        if not h: return None
        return Doctor.from_hash(did, h)

    def get_by_user_id(self, uid: int) -> Optional[Doctor]:
        did = r.get(self.key_doctor_by_user(uid))
        if not did: return None
        return self.get_by_id(int(did))

class AppointmentRepo:
    id_counter = "next_appointment_id"

    @staticmethod
    def key_appt(aid: int) -> str: return f"appointment:{aid}"
    @staticmethod
    def key_patient_appts(pid: int) -> str: return f"patient:{pid}:appointments"
    @staticmethod
    def key_doctor_appts(did: int) -> str: return f"doctor:{did}:appointments"

    def create(self, patient_id: int, doctor_id: int, date: str, time_: str, status: str) -> int:
        now = datetime.utcnow().isoformat()
        aid = int(r.incr(self.id_counter))
        r.hset(self.key_appt(aid), mapping={
            "patient_id": patient_id,
            "doctor_id": doctor_id,
            "appointment_date": date,
            "appointment_time": time_,
            "status": status,
            "created_at": now,
        })
        r.lpush(self.key_patient_appts(patient_id), aid)
        r.lpush(self.key_doctor_appts(doctor_id), aid)
        return aid

    def get_by_id(self, aid: int) -> Optional[Appointment]:
        h = r.hgetall(self.key_appt(aid))
        if not h: return None
        return Appointment.from_hash(aid, h)

    def update_status(self, aid: int, new_status: str) -> bool:
        return r.hset(self.key_appt(aid), "status", new_status) is not None

    def list_by_patient(self, pid: int, limit: int = 50) -> List[Appointment]:
        ids = r.lrange(self.key_patient_appts(pid), 0, limit-1)
        res = []
        for s in ids:
            ap = self.get_by_id(int(s))
            if ap: res.append(ap)
        return res

    def list_by_doctor(self, did: int, limit: int = 50) -> List[Appointment]:
        ids = r.lrange(self.key_doctor_appts(did), 0, limit-1)
        res = []
        for s in ids:
            ap = self.get_by_id(int(s))
            if ap: res.append(ap)
        return res

class MedicalRecordRepo:
    id_counter = "next_medical_record_id"

    @staticmethod
    def key_rec(rid: int) -> str: return f"medical_record:{rid}"
    @staticmethod
    def key_patient_records(pid: int) -> str: return f"patient:{pid}:records"

    def create(self, patient_id: int, doctor_id: int, record_date: str, department: str,
               diagnosis_result: str, notes: str) -> int:
        now = datetime.utcnow().isoformat()
        rid = int(r.incr(self.id_counter))
        r.hset(self.key_rec(rid), mapping={
            "patient_id": patient_id,
            "doctor_id": doctor_id,
            "record_date": record_date,
            "department": department,
            "diagnosis_result": diagnosis_result,
            "notes": notes,
            "created_at": now,
        })
        r.lpush(self.key_patient_records(patient_id), rid)
        return rid

    def get_by_id(self, rid: int) -> Optional[MedicalRecord]:
        h = r.hgetall(self.key_rec(rid))
        if not h: return None
        return MedicalRecord.from_hash(rid, h)

    def list_by_patient(self, pid: int, limit: int = 50) -> List[MedicalRecord]:
        ids = r.lrange(self.key_patient_records(pid), 0, limit-1)
        res = []
        for s in ids:
            rec = self.get_by_id(int(s))
            if rec: res.append(rec)
        return res

class PrescriptionRepo:
    id_counter = "next_prescription_id"

    @staticmethod
    def key_pres(pid: int) -> str: return f"prescription:{pid}"
    @staticmethod
    def key_record_pres(rid: int) -> str: return f"record:{rid}:prescriptions"

    def create(self, record_id: int, doctor_id: int, details: str, creation_date: str) -> int:
        pid = int(r.incr(self.id_counter))
        r.hset(self.key_pres(pid), mapping={
            "record_id": record_id,
            "doctor_id": doctor_id,
            "prescription_details": details,
            "creation_date": creation_date,
        })
        r.lpush(self.key_record_pres(record_id), pid)
        return pid

    def get_by_id(self, pid_: int) -> Optional[Prescription]:
        h = r.hgetall(self.key_pres(pid_))
        if not h: return None
        return Prescription.from_hash(pid_, h)

    def list_by_record(self, rid: int, limit: int = 50) -> List[Prescription]:
        ids = r.lrange(self.key_record_pres(rid), 0, limit-1)
        res = []
        for s in ids:
            pr = self.get_by_id(int(s))
            if pr: res.append(pr)
        return res

class AttendanceRepo:
    id_counter = "next_attendance_id"

    @staticmethod
    def key_att(aid: int) -> str: return f"attendance:{aid}"
    @staticmethod
    def key_doctor_att(did: int) -> str: return f"doctor:{did}:attendances"

    def create(self, doctor_id: int, record_date: str, status: str) -> int:
        now = datetime.utcnow().isoformat()
        aid = int(r.incr(self.id_counter))
        r.hset(self.key_att(aid), mapping={
            "doctor_id": doctor_id,
            "record_date": record_date,
            "status": status,
            "created_at": now,
        })
        r.lpush(self.key_doctor_att(doctor_id), aid)
        return aid

    def get_by_id(self, aid: int) -> Optional[Attendance]:
        h = r.hgetall(self.key_att(aid))
        if not h: return None
        return Attendance.from_hash(aid, h)

    def list_by_doctor(self, did: int, limit: int = 50) -> List[Attendance]:
        ids = r.lrange(self.key_doctor_att(did), 0, limit-1)
        res = []
        for s in ids:
            at = self.get_by_id(int(s))
            if at: res.append(at)
        return res

class ChatRepo:
    id_counter = "next_chat_message_id"

    @staticmethod
    def key_msg(mid: int) -> str: return f"chat_message:{mid}"
    @staticmethod
    def convo_key(a: int, b: int) -> str:
        x, y = (a, b) if a <= b else (b, a)
        return f"chat:between:{x}:{y}"

    def create_message(self, sender_id: int, receiver_id: int, content: str, sent_at: str) -> int:
        mid = int(r.incr(self.id_counter))
        r.hset(self.key_msg(mid), mapping={
            "sender_id": sender_id,
            "receiver_id": receiver_id,
            "message_content": content,
            "sent_at": sent_at,
        })
        r.rpush(self.convo_key(sender_id, receiver_id), mid)
        return mid

    def list_conversation(self, a: int, b: int, limit: int = 100) -> List[ChatMessage]:
        key = self.convo_key(a, b)
        length = r.llen(key)
        start = max(0, length - limit)
        ids = r.lrange(key, start, -1)
        res = []
        for s in ids:
            h = r.hgetall(self.key_msg(int(s)))
            if h:
                res.append(ChatMessage.from_hash(int(s), h))
        return res
