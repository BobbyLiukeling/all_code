# Generated by Django 2.0.4 on 2018-07-26 10:53

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('goods', '0001_initial'),
    ]

    operations = [
        migrations.RenameField(
            model_name='goods',
            old_name='click_nums',
            new_name='click_num',
        ),
        migrations.RenameField(
            model_name='goods',
            old_name='goods_nums',
            new_name='goods_num',
        ),
        migrations.RenameField(
            model_name='goods',
            old_name='sold_nums',
            new_name='sold_num',
        ),
    ]
