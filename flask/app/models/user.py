
from flask_sqlalchemy import SQLAlchemy
import click
from flask.cli import with_appcontext

db = SQLAlchemy()

class  User(db.Model):
   
   id = db.Column(db.Integer, primary_key=True)
   sno = db.Column(db.String(20),unique=True)
   password = db.Column(db.String(20))
   role = db.Column(db.String(2))

   def __init__(self, sno, password, role):
        
     self.sno = sno
     self.password = password 
     self.role = role

   def __repr__(self):
        return '<User %r>' % self.sno

class Commit(db.Model):

  id = db.Column(db.Integer, primary_key=True)
  sno = db.Column(db.Integer,db.ForeignKey('user.sno')) # 大写出错，说明默认小写，还是自定义表名好
  title = db.Column(db.Text)
  content = db.Column(db.Text)

  def __init__(self, sno,title, content):
     self.title = title
     self.sno = sno
     self.content = content 

class Messges(db.Model):

  id = db.Column(db.Integer, primary_key=True)
  sno = db.Column(db.Integer,db.ForeignKey('user.sno')) # 大写出错，说明默认小写，还是自定义表名好
  title = db.Column(db.Text)
  content = db.Column(db.Text)

  def __init__(self, sno,title,content):
     self.title = title
     self.sno = sno
     self.content = content 



    

@click.command('init-db')
@with_appcontext
def init_db_command():
    """Clear the existing data and create new tables."""
    db.create_all()
    click.echo('Initialized the database.')

def init_app(app):
    app.cli.add_command(init_db_command)