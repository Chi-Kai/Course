from flask_wtf import FlaskForm
from wtforms import StringField, SubmitField ,TextAreaField
from wtforms.validators import DataRequired, Length
from flask_ckeditor import CKEditorField,CKEditor #从flask_ckeditor包导入

class RichTextForm(FlaskForm):
    title = StringField('标题', validators=[DataRequired(),Length(1,50,'不能为空')])
    body = CKEditorField('内容', validators=[DataRequired(),Length(1,500,'不能为空')])
    submit = SubmitField('提交')