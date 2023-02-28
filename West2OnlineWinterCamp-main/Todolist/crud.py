#coding:utf-8

from sqlalchemy.orm import Session
from Todolist import schemas, models

# def create_list(db: Session, list: schemas.ListCreate):
#     db_list = models.Lists(**list.dict())
#     db.add(db_list)
#     db.commit()
#     db.refresh(db_list)
#     return db_list

def create_list(db: Session, id: int, title: str, content: str, status: str, add_time: int, dead_time: int):
    try:
        db_list = models.Lists(id=id, title=title, content=content, status=status, add_time=add_time, dead_time=dead_time)
        db.add(db_list)
        db.commit()
        db.refresh(db_list)
        return {"msg": "create successfully"}
    except:
        return {"msg": "unknown error"}

def change_status_by_id(db: Session, list: models.Lists):
    if list.status == 'yes':
        list.status = 'no'
        db.commit()
        return {"msg": "change successfully"}
    elif list.status == 'no':
        list.status = 'yes'
        db.commit()
        return {"msg": "change successfully"}
    else:
        return {"msg": "unknown error"}

def get_all(db: Session):
    lists = db.query(models.Lists).all()
    if lists:
        return lists
    else:
        return {"msg": "not found"}

def get_list_by_id(db: Session, id: int):
    id_list = db.query(models.Lists).filter(models.Lists.id == id).first()
    if id_list:
        return id_list
    else:
        return {"msg": "not found"}

def get_list_by_status(db: Session, status: str):
    status_lists = db.query(models.Lists).filter(models.Lists.status == status).all()
    if status_lists:
        return status_lists
    else:
        return {"msg": "not found"}

def get_list_by_keyword(db: Session, keyword: str):
    keyword_lists = db.query(models.Lists).filter(models.Lists.title.like('%{0}%'.format(keyword))).all()
    if keyword_lists:
        return keyword_lists
    else:
        return {"msg": "not found"}

def delete_list_by_id(db: Session, id: int):
    id_list = db.query(models.Lists).filter(models.Lists.id == id).first()
    if id_list:
        db.delete(id_list)
        db.commit()
        return {"msg": "delete successfully"}
    else:
        return {"msg": "not found"}

def delete_all(db:Session):
    lists = db.query(models.Lists).all()
    if lists:
        for i in lists:
            db.delete(i)
            db.commit()
        return {"msg": "delete successfully"}
    else:
        return {"msg", "not found"}

def delete_list_by_status(db: Session, status: str):
    status_lists = db.query(models.Lists).filter(models.Lists.status == status).all()
    if status_lists:
        for i in status_lists:
            db.delete(i)
            db.commit()
        return {"msg": "delete successfully"}
    else:
        return {"msg": "not found"}