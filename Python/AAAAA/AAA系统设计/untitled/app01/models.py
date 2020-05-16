from django.db import models


class App01Apartment(models.Model):
    id = models.IntegerField(primary_key=True)
    apartment_no = models.ForeignKey('App01Area', models.DO_NOTHING, db_column='apartment_no', blank=True, null=True)
    dormitoryno = models.CharField(max_length=255, blank=True, null=True)
    han = models.CharField(max_length=255, blank=True, null=True)
    others = models.CharField(db_column='others', max_length=255, blank=True,
                                    null=True)  # Field renamed to remove unsuitable characters. Field renamed because it started with '_'.

    class Meta:
        managed = False
        db_table = 'app01apartment'


class App01Area(models.Model):
    apartment_name = models.CharField(db_column='Apartment_name', max_length=32)  # Field name made lowercase.

    class Meta:
        managed = False
        db_table = 'app01area'


class App01Student(models.Model):
    student_no = models.CharField(primary_key=True, max_length=32)
    student_name = models.CharField(max_length=255, blank=True, null=True)
    classes = models.CharField(max_length=255, blank=True, null=True)
    male = models.CharField(max_length=255, blank=True, null=True)
    contact = models.CharField(max_length=255, blank=True, null=True)
    apartment = models.ForeignKey(App01Apartment, models.DO_NOTHING, db_column='apartment', blank=True, null=True)
    nation = models.CharField(db_column='Nation', max_length=255, blank=True, null=True)  # Field name made lowercase.

    class Meta:
        managed = False
        db_table = 'app01student'


class App01Teacher(models.Model):
    teacher_no = models.CharField(primary_key=True, max_length=32)
    teacher_name = models.CharField(max_length=255, blank=True, null=True)
    male = models.CharField(max_length=255, blank=True, null=True)
    contact = models.CharField(max_length=255, blank=True, null=True)
    password = models.CharField(max_length=255, blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'app01teacher'


class Manager(models.Model):
    manage_name = models.CharField(max_length=255, blank=True, null=True)
    password = models.CharField(max_length=255, blank=True, null=True)
    name = models.CharField(max_length=255, blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'manager'
