
from django.urls import path,include,re_path
from . import views
urlpatterns = [
path('blog/',views.home),
path('article/(?P<article_id>[0-9]+)',views.article_page, name = 'article_page'),
path('edit/(?P<article_id>[0-9]+)',views.edit_page, name = 'edit_page'),
path('edit/action',views.edit_action, name = 'edit_action'),
]
app_name = 'blog'