"""
Django settings for MXonline project.

Generated by 'django-admin startproject' using Django 2.0.4.

For more information on this file, see
https://docs.djangoproject.com/en/2.0/topics/settings/

For the full list of settings and their values, see
https://docs.djangoproject.com/en/2.0/ref/settings/
"""

import os
import sys

# Build paths inside the project like this: os.path.join(BASE_DIR, ...)
BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0,os.path.join(BASE_DIR,"apps"))
sys.path.insert(1,os.path.join(BASE_DIR))
sys.path.insert(2,os.path.join(BASE_DIR,"utils"))

# Quick-start development settings - unsuitable for production
# See https://docs.djangoproject.com/en/2.0/howto/deployment/checklist/

# SECURITY WARNING: keep the secret key used in production secret!
SECRET_KEY = '3v$2$&4v#hturch3cej04p#wph7_swfsl%tke*(b$f@i@(f=1i'

# SECURITY WARNING: don't run with debug turned on in production!
# DEBUG = False
DEBUG = True

ALLOWED_HOSTS = []
# ALLOWED_HOSTS = ['*']

AUTHENTICATION_BACKENDS = (
    "users.views.CustomBackend",
)

# Application definition

INSTALLED_APPS = [
    'django.contrib.admin',
    'django.contrib.auth',
    'django.contrib.contenttypes',
    'django.contrib.sessions',
    'django.contrib.messages',
    'django.contrib.staticfiles',
    'users',
    'courses',
    'operation',
    'organization',
    'xadmin',
    'crispy_forms',
    'captcha',
    'pure_pagination',
    'DjangoUeditor',

]
AUTH_USER_MODEL= "users.UserProfile"#注册自定义models字段,appname.modelsclass

MIDDLEWARE = [
    'django.middleware.security.SecurityMiddleware',
    'django.contrib.sessions.middleware.SessionMiddleware',
    'django.middleware.common.CommonMiddleware',
    'django.middleware.csrf.CsrfViewMiddleware',
    'django.contrib.auth.middleware.AuthenticationMiddleware',
    'django.contrib.messages.middleware.MessageMiddleware',
    'django.middleware.clickjacking.XFrameOptionsMiddleware',
]

ROOT_URLCONF = 'MXonline.urls'

TEMPLATES = [
    {
        'BACKEND': 'django.template.backends.django.DjangoTemplates',
        'DIRS': [os.path.join(BASE_DIR,"templates")],
        'APP_DIRS': True,
        'OPTIONS': {
            'context_processors': [
                'django.template.context_processors.debug',
                'django.template.context_processors.request',
                'django.contrib.auth.context_processors.auth',
                'django.contrib.messages.context_processors.messages',
                'django.template.context_processors.media',
            ],
        },
    },
]

WSGI_APPLICATION = 'MXonline.wsgi.application'


# Database
# https://docs.djangoproject.com/en/2.0/ref/settings/#databases

DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.mysql',
        'NAME': "mxonline",
        'USER': "root",
        'PASSWORD': "520lkl",
        'HOST': "127.0.0.1",
        'PORT': "3306",
        # 'OPTIONS': {'init_command': 'SET storage_engine=INNODB;'}
    }
}


# Password validation
# https://docs.djangoproject.com/en/2.0/ref/settings/#auth-password-validators

AUTH_PASSWORD_VALIDATORS = [
    {
        'NAME': 'django.contrib.auth.password_validation.UserAttributeSimilarityValidator',
    },
    {
        'NAME': 'django.contrib.auth.password_validation.MinimumLengthValidator',
    },
    {
        'NAME': 'django.contrib.auth.password_validation.CommonPasswordValidator',
    },
    {
        'NAME': 'django.contrib.auth.password_validation.NumericPasswordValidator',
    },
]


# Internationalization
# https://docs.djangoproject.com/en/2.0/topics/i18n/

LANGUAGE_CODE = 'zh-hans'

TIME_ZONE = 'Asia/Shanghai'

USE_I18N = True

USE_L10N = True

USE_TZ = False


# Static files (CSS, JavaScript, Images)
# https://docs.djangoproject.com/en/2.0/howto/static-files/

STATIC_URL = '/static/'
STATICFILES_DIRS = [os.path.join(BASE_DIR, "static"),]

EMAIL_HOST = 'smtp.qq.com'
EMAIL_POSRT = 25
EMAIL_HOST_USER = "1194380923@qq.com"#邮箱名
EMAIL_HOST_PASSWORD = "xpkdjgkhhwvbgjce"#密码，这里要换成授权码
EMAIL_USE_TLS = False
EMAIL_FROM = "1194380923@qq.com"#邮箱名


#添加图片路径
MEDIA_URL = '/media/'
MEDIA_ROOT = os.path.join(BASE_DIR,'media')






# #分页显示设置
# # PAGINATION_SETTINGS = {
# #     'PAGE_RANGE_DISPLAYED': 10,#总共显示页数
# #     'MARGIN_PAGES_DISPLAYED': 2,#两头显示页数
# #
# #     'SHOW_FIRST_PAGE_WHEN_INVALID': True,#如果出错是否只显示第一页
# # }