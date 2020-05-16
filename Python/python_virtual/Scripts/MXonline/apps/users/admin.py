from django.contrib import admin


from .models import UserProfile
# Register your models here.
class UserProfileAdmin(admin.ModelAdmin):
    list_display = ('nick_name', 'gender', 'address',)  # 支持list和tuple
    list_filter = ('nick_name',)


admin.site.register(UserProfile,UserProfileAdmin)