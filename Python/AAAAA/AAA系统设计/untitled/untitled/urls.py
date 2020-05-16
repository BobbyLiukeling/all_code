"""untitled URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/2.0/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path, re_path
from app01 import views

app_name = '[app01]'
urlpatterns = [
    path('admin/', admin.site.urls),
    path('login/', views.login, name='login'),
    path('teacher/', views.teacher, name='teacher'),
    path('add_student/', views.add_student, name='add_student'),
    path('student_list/', views.student_list, name='student_list'),
    path('delete_student/', views.delete_student, name='delete_student'),
    path('edit_student/', views.edit_student, name='edit_student'),
    path('unallocated/', views.unallocated, name='unallocated'),
    path('text_allocation/', views.text_allocation, name='text_allocation'),
    path('foo/', views.foo, name='foo'),
    path('show_apartment/', views.show_apartment, name='show_apartment'),
    path('excel_export/', views.excel_export, name='excel_export'),
    path('logout/', views.logout, name='logout'),
    path('manager/', views.manager, name='manager'),
    path('show_manager/', views.show_manager, name='show_manager'),
    path('add_manager/', views.add_manager, name='add_manager'),
    path('edit_manager/', views.edit_manager, name='edit_manager'),
    path('del_manager/', views.del_manager, name='def_manager'),
    path('logout_teachername/', views.logout_teachername, name='logout_teachername'),
    path('changePasswordteacher/', views.changePasswordteacher, name='changePasswordteacher'),
    path('changePasswordmanager/', views.changePasswordmanager, name='changePasswordmanager'),

]
