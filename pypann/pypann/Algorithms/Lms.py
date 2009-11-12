#
# Lms
#

from ..Runners import init_net, lms_runner
from Teacher import teach

def lms(net, data):
    if not hasattr(net, "lms_attributes"):
        init_net(net)

    teach(net, data, lms_runner)
    net.lms_attributes.epoch += 1
