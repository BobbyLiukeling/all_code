from django import forms

from .models import UserAsr

# class UserAsrForm(forms.Form):
#     name = forms.CharField(required=True,min_length=2,max_length=20)
#     phone = forms.CharField(required=True,min_length=11,max_length=11)
#     course_name = forms.CharField(required=True,min_length=2)


#forms从models中继承字段，就不用再重新自定义了，解决重复性
class AnotherUserForm(forms.Form):
    #这里还可以增加自定义字段
    class Meta:
        model = UserAsr
        fields = ['name','mobile','course_name']#挑选需要继承的字段名，与models中的字段名一致就OK
