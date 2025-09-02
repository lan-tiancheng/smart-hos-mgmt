# This Python file uses the following encoding: utf-8

# if __name__ == "__main__":
#     pass
from dataclasses import dataclass, asdict
from typing import Optional, Dict, Any

# 注意：所有 datetime 字段均建议存储为 ISO8601 字符串，UTC 时区

@dataclass
class User:
    id: int
    username: str
    password_hash: str
    role: str                  # 'patient' | 'doctor'
    created_at: str

    def to_hash(self) -> Dict[str, Any]:
        return {
            "username": self.username,
            "password_hash": self.password_hash,
            "role": self.role,
            "created_at": self.created_at,
        }

    @staticmethod
    def from_hash(id_: int, h: Dict[str, Any]) -> "User":
        return User(
            id=id_,
            username=h.get("username",""),
            password_hash=h.get("password_hash",""),
            role=h.get("role","patient"),
            created_at=h.get("created_at",""),
        )

@dataclass
class Patient:
    id: int
    user_id: int
    name: str
    gender: str                # 'male' | 'female'
    id_card_number: str
    phone_number: str
    email: str
    created_at: str

    def to_hash(self) -> Dict[str, Any]:
        return {
            "user_id": self.user_id,
            "name": self.name,
            "gender": self.gender,
            "id_card_number": self.id_card_number,
            "phone_number": self.phone_number,
            "email": self.email,
            "created_at": self.created_at,
        }

    @staticmethod
    def from_hash(id_: int, h: Dict[str, Any]) -> "Patient":
        return Patient(
            id=id_,
            user_id=int(h.get("user_id", 0) or 0),
            name=h.get("name",""),
            gender=h.get("gender","male"),
            id_card_number=h.get("id_card_number",""),
            phone_number=h.get("phone_number",""),
            email=h.get("email",""),
            created_at=h.get("created_at",""),
        )

@dataclass
class Doctor:
    id: int
    user_id: int
    work_id: str
    name: str
    department: str
    personal_profile: str
    photo_url: str
    consultation_fee: str      # 保存为字符串，或自行转为 decimal 的字符串
    created_at: str

    def to_hash(self) -> Dict[str, Any]:
        return {
            "user_id": self.user_id,
            "work_id": self.work_id,
            "name": self.name,
            "department": self.department,
            "personal_profile": self.personal_profile,
            "photo_url": self.photo_url,
            "consultation_fee": self.consultation_fee,
            "created_at": self.created_at,
        }

    @staticmethod
    def from_hash(id_: int, h: Dict[str, Any]) -> "Doctor":
        return Doctor(
            id=id_,
            user_id=int(h.get("user_id", 0) or 0),
            work_id=h.get("work_id",""),
            name=h.get("name",""),
            department=h.get("department",""),
            personal_profile=h.get("personal_profile",""),
            photo_url=h.get("photo_url",""),
            consultation_fee=h.get("consultation_fee","0.00"),
            created_at=h.get("created_at",""),
        )

@dataclass
class Appointment:
    id: int
    patient_id: int
    doctor_id: int
    appointment_date: str      # 'YYYY-MM-DD'
    appointment_time: str      # 'HH:MM:SS'
    status: str                # 'pending'|'confirmed'|'completed'|'cancelled'
    created_at: str

    def to_hash(self) -> Dict[str, Any]:
        return {
            "patient_id": self.patient_id,
            "doctor_id": self.doctor_id,
            "appointment_date": self.appointment_date,
            "appointment_time": self.appointment_time,
            "status": self.status,
            "created_at": self.created_at,
        }

    @staticmethod
    def from_hash(id_: int, h: Dict[str, Any]) -> "Appointment":
        return Appointment(
            id=id_,
            patient_id=int(h.get("patient_id",0) or 0),
            doctor_id=int(h.get("doctor_id",0) or 0),
            appointment_date=h.get("appointment_date",""),
            appointment_time=h.get("appointment_time",""),
            status=h.get("status","pending"),
            created_at=h.get("created_at",""),
        )

@dataclass
class MedicalRecord:
    id: int
    patient_id: int
    doctor_id: int
    record_date: str           # 'YYYY-MM-DD'
    department: str
    diagnosis_result: str
    notes: str
    created_at: str

    def to_hash(self) -> Dict[str, Any]:
        return {
            "patient_id": self.patient_id,
            "doctor_id": self.doctor_id,
            "record_date": self.record_date,
            "department": self.department,
            "diagnosis_result": self.diagnosis_result,
            "notes": self.notes,
            "created_at": self.created_at,
        }

    @staticmethod
    def from_hash(id_: int, h: Dict[str, Any]) -> "MedicalRecord":
        return MedicalRecord(
            id=id_,
            patient_id=int(h.get("patient_id",0) or 0),
            doctor_id=int(h.get("doctor_id",0) or 0),
            record_date=h.get("record_date",""),
            department=h.get("department",""),
            diagnosis_result=h.get("diagnosis_result",""),
            notes=h.get("notes",""),
            created_at=h.get("created_at",""),
        )

@dataclass
class Prescription:
    id: int
    record_id: int
    doctor_id: int
    prescription_details: str
    creation_date: str         # ISO DATETIME

    def to_hash(self) -> Dict[str, Any]:
        return {
            "record_id": self.record_id,
            "doctor_id": self.doctor_id,
            "prescription_details": self.prescription_details,
            "creation_date": self.creation_date,
        }

    @staticmethod
    def from_hash(id_: int, h: Dict[str, Any]) -> "Prescription":
        return Prescription(
            id=id_,
            record_id=int(h.get("record_id",0) or 0),
            doctor_id=int(h.get("doctor_id",0) or 0),
            prescription_details=h.get("prescription_details",""),
            creation_date=h.get("creation_date",""),
        )

@dataclass
class Attendance:
    id: int
    doctor_id: int
    record_date: str           # 'YYYY-MM-DD'
    status: str                # 'clocked_in'|'leave'
    created_at: str

    def to_hash(self) -> Dict[str, Any]:
        return {
            "doctor_id": self.doctor_id,
            "record_date": self.record_date,
            "status": self.status,
            "created_at": self.created_at,
        }

    @staticmethod
    def from_hash(id_: int, h: Dict[str, Any]) -> "Attendance":
        return Attendance(
            id=id_,
            doctor_id=int(h.get("doctor_id",0) or 0),
            record_date=h.get("record_date",""),
            status=h.get("status","clocked_in"),
            created_at=h.get("created_at",""),
        )

@dataclass
class ChatMessage:
    id: int
    sender_id: int
    receiver_id: int
    message_content: str
    sent_at: str

    def to_hash(self) -> Dict[str, Any]:
        return {
            "sender_id": self.sender_id,
            "receiver_id": self.receiver_id,
            "message_content": self.message_content,
            "sent_at": self.sent_at,
        }

    @staticmethod
    def from_hash(id_: int, h: Dict[str, Any]) -> "ChatMessage":
        return ChatMessage(
            id=id_,
            sender_id=int(h.get("sender_id",0) or 0),
            receiver_id=int(h.get("receiver_id",0) or 0),
            message_content=h.get("message_content",""),
            sent_at=h.get("sent_at",""),
        )
