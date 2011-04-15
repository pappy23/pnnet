from django.conf.urls.defaults import *

urlpatterns = patterns('',
    (r'face$', 'main.views.faces_list_all'),
    (r'dataset$', 'main.views.datasets_list_all'),
    (r'net$', 'main.views.nets_list_all'),
    (r'test$', 'main.views.test'),
    (r'log$', 'main.views.logs_list_all'),
    (r'html/(?P<path>.*)$', 'django.views.static.serve', {'document_root': '/home/booble/pann/trunk/src/Apps/hybrid/pann_web/main/html'}),

    (r'$', 'main.views.index'),
)
