import functools

from flask import (
    Blueprint, flash, g, redirect, render_template, request, session, url_for
)



ve = Blueprint('view',__name__,url_prefix='/view')

@ve.route('/index')
def index():
    return render_template('index.html')

@ve.route('/image')
def image():
    return render_template('image.html')

@ve.route('/sound')
def sound():
    return render_template('sound.html')

@ve.route('/video')
def video():
    return render_template('video.html')




@ve.route('/work')
def work():
    return render_template('works.html')


@ve.route('/join')
def join():
    return redirect('https://github.com/Chi-Kai/multimedia-technology')


@ve.route('/more')
def more():
    return redirect('https://bb.dlmu.edu.cn/webapps/bb-sso-BBLEARN/index.jsp') 

@ve.route('/XM')
def XM():
    return render_template('xm.html')

@ve.route('/HM')
def HM():
    return render_template('HM.html')

@ve.route('/CM')
def CM():
    return render_template('cm.html')

@ve.route('/MIDI')
def MIDI():
    return render_template('MIDI.html')


@ve.route('/avs')
def avs():
    return render_template('avs.html')


@ve.route('/AC')
def AC():
    return render_template('Arithmeticcoding.html')



@ve.route('/MP3')
def MP3():
    return render_template('MP3.html')


@ve.route('/RA')
def RA():
    return render_template('RA.html')


@ve.route('/WAV')
def WAV():
    return render_template('WAV.html')




@ve.route('/lab')
def lab():
    return redirect('http://127.0.0.1:8081/') 

# 文本编辑

from  ..extensions import editor 
import sys
sys.path.append(r"app")
from models.user import Commit,User,db,Messges

from .auth import login_required






@ve.route('/ckeditor', methods=['GET', 'POST'])
@login_required
def ckeditor():

    form = editor.RichTextForm()
    if form.validate_on_submit():
 
        content = Commit(g.user.sno,request.form['title'],request.form['body'])
        db.session.add(content)
        db.session.commit()  # 提交才能写入
        flash('提交成功，等待审核')
        return redirect(url_for(('view.index')))

    return render_template('editor.html',form = form)   
        

@ve.route('/messges')
def messages():

    messges = Messges.query.all()
    return render_template('messages.html',messges=messges)
    