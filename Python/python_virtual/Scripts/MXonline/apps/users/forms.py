from django import forms
from captcha.fields import CaptchaField

from .views import UserProfile


class LoginForm(forms.Form):
    username = forms.CharField(required=True)#username 必须要和HTML中的name中的信息一样
    password = forms.CharField(required=True, min_length=5)


class RegisterForm(forms.Form):
    email = forms.EmailField(required=True)
    password = forms.CharField(required=True, min_length=5)
    captcha = CaptchaField(error_messages={"invalid":"验证码错误"})


class ForgetForm(forms.Form):
    email = forms.EmailField(required=True)
    captcha = CaptchaField(error_messages={"invalid":"验证码错误"})


class ModifyPwdForm(forms.Form):
    password1 = forms.CharField(required=True, min_length=5)
    password2 = forms.CharField(required=True, min_length=5)


class UploadImgForm(forms.ModelForm):
    class Meta:
        model = UserProfile
        fields = ['image',]


class UserInfoForm(forms.ModelForm):
    class Meta:
        model = UserProfile
        fields = ['username','birthday','mobile','gender','address']


class TestForm(forms.Form):
    # username = forms.CharField()
    captcha = CaptchaField(error_messages={"invalid":"验证码错误"})