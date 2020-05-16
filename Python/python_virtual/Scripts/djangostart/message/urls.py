
from django.urls import path,include
from . import views

urlpatterns = [
    path("message/", views.getform),
    path("getpost/", views.getpost,name = 'getpost'),
    #name 的作用是在配置路由的时候使用 url 'message:getpost'这个getpost是name = 'getpost'中的getpost
]

app_name = 'message'