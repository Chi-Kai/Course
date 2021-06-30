
from flask import (
    Blueprint, flash, g, redirect, render_template, request, session, url_for
)

import functools

from ..models.user  import db, User

bp = Blueprint('auth', __name__, url_prefix='/auth')


@bp.route('/login', methods=('GET', 'POST'))
def login():
    if request.method == 'POST':
        s = request.form['sno']
        p = request.form['password']
        
        error = None
        user = User.query.filter_by(sno = s , password = p ).first()

        if user is None:
            error = 'Incorrect user.'

        if error is None:
            session.clear()
            session['id'] = user.id
          
            return redirect(url_for('view.index'))

        flash(error)

    return render_template('login.html')

@bp.before_app_request
def load_logged_in_user():

 user = session.get('id')

 if user is None:
 
    g.user = None
 
 else:

    g.user = User.query.filter_by(id = session['id'] ).first()
    

def login_required(view):
    @functools.wraps(view)
    def wrapped_view(**kwargs):
        if g.user is None:
            return redirect(url_for('auth.login'))

        return view(**kwargs)

    return wrapped_view





@bp.route('/logout')
def logout():
    session.clear()
    return redirect(url_for('view.index'))

@bp.route('/admin')
def admin():
    return redirect('http://127.0.0.1:5000/admin')

from  ..models.user import Messges
from  ..extensions import editor 

@bp.route('/ckeditor', methods=['GET', 'POST'])
@login_required
def ckeditor():

    form = editor.RichTextForm()
    if form.validate_on_submit():
 
        content = Messges(g.user.sno,request.form['title'],request.form['body'])
        db.session.add(content)
        db.session.commit()  # 提交才能写入
        return redirect(url_for(('view.messages')))

    return render_template('editor.html',form = form)   

