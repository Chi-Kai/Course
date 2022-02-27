from flask_admin import Admin,BaseView,expose,AdminIndexView
from flask_admin.contrib.sqla import ModelView
from  ..models.user import User,db,Commit,Messges

def init_model(app):

     admin = Admin(
             app,
             name='后台'          
             )

     admin.add_view(ModelView(User, db.session))
     admin.add_view(ModelView(Commit, db.session))
     admin.add_view(ModelView(Messges, db.session))
     