# Generated by Django 2.0.4 on 2018-06-22 15:17

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('organization', '0001_initial'),
    ]

    operations = [
        migrations.AlterField(
            model_name='teacher',
            name='name',
            field=models.CharField(max_length=50, verbose_name='教师名称'),
        ),
    ]