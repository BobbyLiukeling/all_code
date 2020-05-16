from django import forms
import re

from operation.models import UserAsr


class UserAskForm(forms.ModelForm):
    class Meta:
        model = UserAsr
        fields = ['name','mobile','course_name']

    def clean_mobile(self):
        mobile = self.cleaned_data['mobile']
        MOBILE = "^1[358]\d{9}$|^147\d{8}$|^176\d{8}$"
        p = re.compile(MOBILE)
        if p.match(mobile):
            return mobile
        else:
            raise forms.ValidationError("手机号码非法", code = "mobile_invalid")