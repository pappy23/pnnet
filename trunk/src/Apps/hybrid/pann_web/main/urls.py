from django.conf.urls.defaults import *

urlpatterns = patterns('',
    (r'face$', 'main.views.faces_list_all'),
    (r'log$', 'main.views.logs_list_all')
)
