import xadmin
from .models import UserFav,UserAddress,UserLeavingMessage


class UserFavAdmin(object):
    list_display = ['user','goods','add_time']
    list_filter = ['user__name','goods__name','add_time']
    search_filter = ['user','goods']


class UserLeavingMessageAdmin(object):
    list_display = ['user','message_type','subject','message','file','add_time']
    list_filter = ['user__name','message_type','subject','message','file','add_time']
    search_filter = ['user','message_type','subject','message','file']


class UserAddressAdmin(object):
    list_display = ['user','district','address','signer_name','signer_mobile','add_time']
    list_filter = ['user__name','district','address','signer_name','signer_mobile','add_time']
    search_filter = ['user','district','address','signer_name','signer_mobile']


xadmin.site.register(UserFav,UserFavAdmin)
xadmin.site.register(UserLeavingMessage,UserLeavingMessageAdmin)
xadmin.site.register(UserAddress,UserAddressAdmin)