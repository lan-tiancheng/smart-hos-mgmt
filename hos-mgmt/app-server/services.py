from typing import Optional, Tuple, List
from werkzeug.security import generate_password_hash, check_password_hash
from datetime import datetime

# 修正导入：绝对导入
from repositories import (
    UserRepo, PatientRepo, DoctorRepo, AppointmentRepo,
    MedicalRecordRepo, PrescriptionRepo, AttendanceRepo, ChatRepo
)
from domain.entities import User, Patient, Doctor, Appointment, MedicalRecord, Prescription, Attendance, ChatMessage

class AuthService:
    def __init__(self):
        self.users = UserRepo()
        self.patients = PatientRepo()
        self.doctors = DoctorRepo()

    def register_user(self, username: str, password: str, role: str,
                      patient_info: dict = None, doctor_info: dict = None) -> Tuple[Optional[int], Optional[str]]:
        pwd_hash = generate_password_hash(password)
        uid, err = self.users.create_user(username=username, password_hash=pwd_hash, role=role)
        if err: return None, err

        if role == "patient":
            patient_info = patient_info or {}
            pid, err2 = self.patients.create_patient(
                user_id=uid,
                name=patient_info.get("name",""),
                gender=patient_info.get("gender","male"),
                id_card_number=patient_info.get("id_card_number",""),
                phone=patient_info.get("phone_number",""),
                email=patient_info.get("email","")
            )
            if err2:
                return None, f"创建患者失败: {err2}"
        elif role == "doctor":
            doctor_info = doctor_info or {}
            did, err2 = self.doctors.create_doctor(
                user_id=uid,
                work_id=doctor_info.get("work_id",""),
                name=doctor_info.get("name",""),
                department=doctor_info.get("department",""),
                personal_profile=doctor_info.get("personal_profile",""),
                photo_url=doctor_info.get("photo_url",""),
                consultation_fee=str(doctor_info.get("consultation_fee","0.00")),
            )
            if err2:
                return None, f"创建医生失败: {err2}"

        return uid, None

    def login(self, username: str, password: str) -> Tuple[Optional[User], Optional[str]]:
        u = self.users.get_by_username(username)
        if not u: return None, "用户不存在"
        if not check_password_hash(u.password_hash, password):
            return None, "用户名或密码错误"
        return u, None

class AppointmentService:
    def __init__(self):
        self.appts = AppointmentRepo()
        self.patients = PatientRepo()
        self.doctors = DoctorRepo()

    def create_appointment(self, user_id_patient: int, doctor_id: int, date: str, time_: str) -> Tuple[Optional[int], Optional[str]]:
        pat = self.patients.get_by_user_id(user_id_patient)
        if not pat:
            return None, "未找到患者资料"
        doc = self.doctors.get_by_id(doctor_id)
        if not doc:
            return None, "医生不存在"
        aid = self.appts.create(patient_id=pat.id, doctor_id=doctor_id, date=date, time_=time_, status="pending")
        return aid, None

    def list_for_patient_user(self, user_id_patient: int, limit: int = 50) -> List[Appointment]:
        pat = self.patients.get_by_user_id(user_id_patient)
        if not pat:
            return []
        return self.appts.list_by_patient(pat.id, limit=limit)

    def list_for_doctor(self, doctor_id: int, limit: int = 50) -> List[Appointment]:
        return self.appts.list_by_doctor(doctor_id, limit=limit)

class MedicalService:
    def __init__(self):
        self.records = MedicalRecordRepo()
        self.pres = PrescriptionRepo()
        self.patients = PatientRepo()
        self.doctors = DoctorRepo()

    def create_record(self, patient_user_id: int, doctor_id: int, record_date: str, department: str,
                      diagnosis_result: str, notes: str) -> Tuple[Optional[int], Optional[str]]:
        pat = self.patients.get_by_user_id(patient_user_id)
        if not pat:
            return None, "未找到患者资料"
        doc = self.doctors.get_by_id(doctor_id)
        if not doc:
            return None, "医生不存在"
        rid = self.records.create(patient_id=pat.id, doctor_id=doctor_id, record_date=record_date,
                                  department=department, diagnosis_result=diagnosis_result, notes=notes)
        return rid, None

    def add_prescription(self, record_id: int, doctor_id: int, details: str) -> Tuple[int, None]:
        pid = self.pres.create(record_id=record_id, doctor_id=doctor_id, details=details,
                               creation_date=datetime.utcnow().isoformat())
        return pid, None

class AttendanceService:
    def __init__(self):
        self.repo = AttendanceRepo()

    def clock_in(self, doctor_id: int, date: str) -> int:
        return self.repo.create(doctor_id=doctor_id, record_date=date, status="clocked_in")

    def leave(self, doctor_id: int, date: str) -> int:
        return self.repo.create(doctor_id=doctor_id, record_date=date, status="leave")

class ChatService:
    def __init__(self):
        self.repo = ChatRepo()

    def send_message(self, sender_id: int, receiver_id: int, content: str) -> int:
        return self.repo.create_message(sender_id=sender_id, receiver_id=receiver_id, content=content,
                                        sent_at=datetime.utcnow().isoformat())

    def list_conversation(self, a: int, b: int, limit: int = 100) -> List[ChatMessage]:
        return self.repo.list_conversation(a, b, limit=limit)
