# Generated by Django 2.0.4 on 2018-07-28 03:34

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('goods', '0004_auto_20180726_2149'),
    ]

    operations = [
        migrations.AlterField(
            model_name='goodscategory',
            name='category_type',
            field=models.IntegerField(choices=[(1, '一级类别'), (2, '二级类别'), (3, '三级类别')], help_text='类目级别', max_length=10, verbose_name='类目级别'),
        ),
    ]