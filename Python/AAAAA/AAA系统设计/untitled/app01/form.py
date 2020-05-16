from django import forms


class LoginForm(forms.Form):
    username = forms.CharField(widget=forms.TextInput(attrs={"placeholder": "用户名", "required": "required", }),
                               max_length=50, error_messages={"required": "用户名不能为空", })
    password = forms.CharField(widget=forms.PasswordInput(attrs={"placeholder": "密码", "required": "required", }),
                               max_length=20, error_messages={"required": "密码不能为空", })