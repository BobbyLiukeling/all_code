# Generated by Django 2.0.4 on 2018-08-07 16:24

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('users', '0004_auto_20180807_1353'),
    ]

    operations = [
        migrations.AlterField(
            model_name='userprofile',
            name='gender',
            field=models.CharField(choices=[('male', '男'), ('female', '女')], default='male', max_length=6),
        ),
        migrations.AlterField(
            model_name='userprofile',
            name='image',
            field=models.ImageField(blank=True, default=None, upload_to='users/%Y/%m', verbose_name='用户头像'),
        ),
        migrations.AlterField(
            model_name='userprofile',
            name='name',
            field=models.CharField(blank=True, default=None, max_length=20, verbose_name='用户名'),
        ),
        migrations.AlterField(
            model_name='userprofile',
            name='profession',
            field=models.CharField(blank=True, default=None, max_length=50, verbose_name='职业'),
        ),
        migrations.AlterField(
            model_name='userprofile',
            name='sign',
            field=models.CharField(blank=True, default=None, max_length=50, verbose_name='个性签名'),
        ),
    ]
