# Generated by Django 2.0.4 on 2018-07-12 21:56

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('courses', '0008_course_teacher'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='course',
            name='teacher',
        ),
    ]