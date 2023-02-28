from typing import Optional
from pydantic import BaseModel, constr

class ListBase(BaseModel):
    title: str
    content: Optional[str] = None
    status: str
    add_time: int
    dead_time: int

class ListCreate(ListBase):
    id: int

    class Config:
        orm_mode = True

class List(ListBase):
    id: int

    class Config:
        orm_mode = True

