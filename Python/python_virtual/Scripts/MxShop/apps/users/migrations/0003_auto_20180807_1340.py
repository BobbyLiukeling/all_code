# Generated by Django 2.0.4 on 2018-08-07 13:40

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('users', '0002_auto_20180801_1114'),
    ]

    operations = [
        migrations.RenameField(
            model_name='verifycodede',
            old_name='code',
            new_name='identifying',
        ),
    ]
