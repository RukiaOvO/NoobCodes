from sqlalchemy import Column, Integer, String
from Todolist.database import Base

class Lists(Base):
    __tablename__ = "list"
    id = Column(Integer, primary_key=True, index=True)
    title = Column(String(255), index=True)
    content = Column(String(255), index=True)
    status = Column(String(255), index=True)
    add_time = Column(Integer, index=True)
    dead_time = Column(Integer, index=True)