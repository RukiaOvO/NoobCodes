#coding:utf-8
from fastapi import FastAPI, Depends, HTTPException
from typing import List
from sqlalchemy.orm import Session
from Todolist import crud, schemas, models
from Todolist.database import SessionLocal, engine
import uvicorn

models.Base.metadata.create_all(bind=engine)

app = FastAPI()

def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()

@app.get("/", tags=["Home"])#Home Page
async def index():
    """This is Home Page"""
    return {"msg": "This is Home Page"}

# @app.post("/add", tags=["Todolist"], response_model=schemas.List)#增
# async def create_one_list(list: schemas.ListCreate, db: Session = Depends(get_db)):
#     """增加一条待办事项"""
#     return crud.create_list(db=db, list=list)

@app.post("/add", tags=["Todolist"])#增
async def create(id: int, title: str, content: str, status: str, add_time: int, dead_time: int, db: Session = Depends(get_db)):
    if status == 'yes' or status == 'no':
        return crud.create_list(id=id, title=title, content=content, status=status, add_time=add_time, dead_time=dead_time, db=db)
    else:
        return {"msg": "value_status error"}

@app.post("/change/{id}", tags=["Todolist"])#改
async def change_status(id: int, db: Session = Depends(get_db)):
    """根据id修改事项状态"""
    list = db.query(models.Lists).filter(models.Lists.id == id).first()
    if list:
        return crud.change_status_by_id(db=db, list=list)
    else:
        return {"msg", "not found"}

@app.get("/check/{order}", tags=["Todolist"])#查
async def check(order: str, db: Session = Depends(get_db)):
    """查看事项 \n
    check_id 根据id查看事项 \n
    check_all 查看所有事项 \n
    check_yes 查看所有已完成事项 \n
    check_no 查看所有待办事项 \n
    check_关键字 关键字查看事项 \n
    """
    try:
        key = order.split("_")
        if key:
            try:
                id = int(key[1])
                return crud.get_list_by_id(db=db, id=id)
            except:
                if key[1] == 'all':
                    return crud.get_all(db=db)

                elif key[1] == 'yes':
                    return crud.get_list_by_status(db=db, status='yes')

                elif key[1] == 'no':
                    return crud.get_list_by_status(db=db, status='no')
                else:
                    keyword = key[1]
                    return crud.get_list_by_keyword(db=db, keyword=keyword)
    except:
        return {"msg": "order error"}

@app.delete("/delete/{order}", tags=["Todolist"])#删
async def delete(order: str, db: Session = Depends(get_db)):
    """删除事项 \n
    delete_id 根据id删除事项 \n
    delete_all 删除所有事项 \n
    delete_yes 删除所有已完成事项 \n
    delete_no 删除所有待办事项 \n
    """
    try:
        key = order.split("_")
        if key:
            try:
                id = int(key[1])
                return crud.delete_list_by_id(db=db, id=id)

            except:
                if key[1] == 'all':
                    return crud.delete_all(db=db)

                elif key[1] == 'yes':
                    return crud.delete_list_by_status(db=db, status='yes')

                elif key[1] == 'no':
                    return crud.delete_list_by_status(db=db, status='no')

                return {"msg": "order error"}
    except:
        return {"msg": "order error"}

if __name__ == '__main__':
    uvicorn.run(app)
