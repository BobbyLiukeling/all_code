# Generated by Django 2.0.4 on 2018-07-26 13:49

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('goods', '0003_auto_20180726_1912'),
    ]

    operations = [
        migrations.RenameField(
            model_name='goods',
            old_name='goods_front_img',
            new_name='goods_front_image',
        ),
    ]
