from django.conf.urls.defaults import *

urlpatterns = patterns('',
    (r'face$', 'main.views.faces_list_all'),
    (r'dataset$', 'main.views.datasets_list_all'),
    (r'net$', 'main.views.nets_list_all'),
    (r'log$', 'main.views.logs_list_all'),
    (r'info$', 'main.views.info_list_all'),
    (r'nets_actions', 'main.views.nets_actions'),
    (r'nets_rename', 'main.views.nets_rename'),
    (r'nets_showsize', 'main.views.nets_showsize'),
    (r'nets_load', 'main.views.nets_rename'),
    (r'nets_rename', 'main.views.nets_rename'),
    (r'nets_rename', 'main.views.nets_rename'),
    (r'nets_rename', 'main.views.nets_rename'),
    (r'nets_rename', 'main.views.nets_rename'),
    (r'nets_rename', 'main.views.nets_rename'),
#    (r'html/(?P<path>.*)$', 'django.views.static.serve', {'document_root': '/home/booble/pann/trunk/src/Apps/hybrid/pann_web/main/html'}),

    (r'$', 'main.views.index'),
)
