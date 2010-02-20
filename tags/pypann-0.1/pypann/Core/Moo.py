#
# Moo
#

__moo_iter = 0

def moo():
    """This moooes =)"""
    global __moo_iter
    if __moo_iter == 0:
        print """
         .:IHHMHHI:..,
  . :HI..IIHHMMMHIHHH:..
 . : H:HMHHMMMMMHMMHMHI::,
 I:HMHMHMHHHMMMMMMMMMH::..:
: M:MMMMMHMMMMMMHMMMMMMMMMI:
 M MMMMMMMMMHMMHMMMMMMMMMM,:
: M:MMMMMMMMMMMMMMMMMMMMMMM,
 H:H:MMMMMMMMHMMMMHHMMMMMM:..
  M:MMMHMMMMMMHHMMMMMMMMMMMMM
 :M:M:M:MHMMHHHI'  '::I HMMMMMI
: M:M:MMMMMMMMHHI, '   HIHMMMMMM.
 M:M:M:MMMMMMMIII,     '':IHMMMM
: M:MMMMMHMMMMMMH:      ... HMMM:
 M:M:MMMMMMMMMMHHH        IMM MH,
M MMMMMMMMMMMMMMMI,   ...IMMMMMM
 M:MMMHMMMMMMMMMMM      :MIMMI.,
: M:MMMHHMMMMMMMM IMMI..  IMMIHH:.
 M:MMMMHHHHHMMMMIMMH:::... 'IHI,...
M MMMMMMMMMMMMM'H:MHIII:...:  ':.:.
 M:MMHHMMHHMHI ,,MMMII:'::I:I.  :I::
M MMMMMMMHH....:'''''::.::I,.: MII:
 M:MMMMMM::.::'''   '':::IH:IM:: IM.
M MMMMMMMMII:'' '    ''::I::  :MMMM.
 M:MMMMMMMII:.        ':I:.,MMMMM':
: M:MMMMMHHHII:.     .::I:IIMMM':::
 M:M:MMMMMMMMII::.. .:II: '::II:''.,:''''::..,
: M:MMMMMMMMMMI:::.:I::.. .. ..:'' ,.:'''::,   ':,
 .:M:MMMMMMHII::'II::....' .:'                   ::.,
  , M:MMMMMMMMMMHI::....::::: :'        ::           '.
    : H:MMMMMMMHHHHHI:..::::II::' .::::::III:,,         ',
      'IHMMMHHHHHHIHIIIIHHHH:    ,'' ::,   .::..          '',
         'MMMHHHHHIIHHHHHHHII: .:::    ::::::::......   ....:,
          MMHHHHHHHIHIIHHIIII  '...''''   '''H:IIHII...    ...',
         .MMHHHHHHHHHHIIIIII':' .....    .:::::II.  'HHH:..   .. ,
        .MMMMMHHHHII::'''  ''       ..     .....:HI:,  II:..  ...::
       ,MHMMMMMHH:.''      ...            ..   ...::H:,  'I::.    .:
      .IMHMMMHI:''     ..:. I       ..    ..    ...::II,  'II....   ::
      IMHIMMI:''         . :                      ....::H:  I:: .    ..
      MMHIMMI:.''    ..:    ...:            ...      ....II,'I:....    .
     'MMHIMM:'':.    .         .. .     .. ,:           ,.IIHI:::.
     IMIHMMI:::''           .     ,                  .,,  ..::IHIII..
     IMIHMMM.......                .                         ..::HH:..
     HMIHMMMH:.       .                                    ...:::IIHI .
     IHIMMM::...                                              '''::::: .
     :MMHMM:..  .       ...       I II..... .                     ' ' ::
     'MIHMMI:...       :::..    .     I. :::::.. ...::....  ..         ' ' 
      MMHMMM:...  ..         .:.....:.III:::.........::::........   ..
      HMIMMI:...         ..:::::::::III:H:IIHII:::::...::::.........
      IMHIMM:.....         ....:::::III:IIIHHHHHHH'III:....:..........
      'MHHMM:...           ....:::::IIIIHMI:':::IHHMHIII:::::..........
       IMIMM:::...            ...:::::III' :....::::IHHMHIIII.::.:.... .
       'MMIMM:...             ....::I:.'  '      ''''::IIIHMH,':::::::: ..
        IMHMMI:::....       ,    ..::::::..    .. ...   ..::IHMM:,'''::;;:. .
         HMMMMH......:  .         ..::::::..            ..::::MMMM)
         IMIMMHH:...:...     ..  ...:::::...   ..  ...  ..:,::MMMI
          HMHMMHI:... ..:.       ....:::::::..:.      ....::::IMM'
          'MMHHHHI:..::...     ....::::II::.::....  ..: ...::IHM'
           IMMHHI:.:::... .      ......::III:..::.::::::..IIHHM'
           'MMMHI:::..::.       ......:IIIHIHII::IHHHHHHHHHI''
            MIMHHHII::..:.    .. ..:::I::.:HHHHIHMMMHMHHIH'
            'MMHHHHII::. ...        ..:.::HHHHHHHMHHMMHI'
             IMMHHIII:::...       .....IHHIIHHIIIHHHHMH
             'MMHHHIII:..:..   ..  ...:HI:...:::IIHHHMH
              IMHHHII::::...       ..IHI..  ..:HHHIHMHH
              'MHHII:::....       ...III:...  .IHHHHMMH
               IMHHHIII::...    ..  ..IHH..  ..:::IHHMH
               'MHHHIIIII:... .    ....II:....:::IHMMHI
                MHHIIII:::::.        ...:::..:::.HHHHH'
                'MMHI::::.......       ..:::::.IHHHIHH
                 MMIII::::.......    ....::::::HIIHHH'
                 'MHHHHHII::...         ...:::::MHHHH
                  MHHHHHHIIH::.           .::::HIMMH'
                  HMHHHHHHHHH::..       ....:::HHHHI
                  IMMHHHHHIIII:.    ..   ..::::IHHM'
                  IMMHHHHHHHHHI::.    ..  ..::HMHHH
                  IMHHHHHHHIII::....   ......::HHHI
                  HMHHHHHHIII::''' '   '''''::MHHM'
                 IMMHHHIII::'''            '::HMMM
                ,HMHHHII::''''         ''''::MMMHM
               IHMHHHHH:''   ''        ''':IHMMMMI
              ,HMHHHHII::.            ''..::MMMMM'
             ,HMHHII::''          ''''':HHHIHMMMM
            ,HMHHI::.              ''::IIIMMHHMMM
          ,IHMMH::''               ..''IHIIMMHMMH
         ,HMHHI:''              ...   .IIIHIMHMHH
        ,HMMI:'          .        ...   ::H MMHHI
       :HMHI:'           ..   ... ....:::. MMMHH'
      IHMHHHI:     .         ...  ....:::::MMHIM
    ,IHMHHHHII::.             .....  ....::::MM'
   ,HMMHHHHII::.                     ....:::MH'
   HMHHHHHHII:::.        ......     ...:::..IM'
  MMMHHHHIII::,             ....::..   ..:::M'
 :MHHHHHIII::'                ....::..:::.:IM'
 MMHHHHHIII::'                ....::::.::IHM'
,MIHHHHHHHII.  .                   :::. .:III
IMIHHHHMMHHII                     ''::::::II:,
HMIHHMMHHHHH::.                 '' :::IIH::,:,
MMHHHHHHHII::'                    ''::::::II::,
HMHHHHHHHHHI:'          ..       ..:   :::::....
IMMHHHHHHHHH::..                  ...:::::..:II::.
'MMHHHHHHHHH::::.          ....    ....::::.::I::.,
 IMMIHHHHHHHHHII::.              ....::::::...:::::.
 'MMMHHHHHHHHHHII::.           ...    ........::::::,
  HMMMHHHHHHHHHIIII::.        ....:::.   ....::::..:..
  'HMMMHHHHHHHHHHIII:::.,       ,,:          ...::..:,.
    MMHMMHHHHHHHHIIII::::...      ...:.     ..  ...::::.
    MMHHMMMHHHHHHHHHHHHHI::...                  ......::.
    MMMIHHMMMHHHHHHHHIIIII:::...     ...:             ...:
    MMMMIHMMMMMMHHHMHHHHHHHIIII:::...::            .....::.
    MMMMMIHMMMMHHHHMHHHHMHHH::.I:..          ...      ....:.
    MMMIHHIHHHMMHHHHMMMHHHHHMMHH::.   ...         ....  ..::.
    MMMMHHHIHHHHMHHHHHHMMMHHHHHHIII:::..,         ....  ...::.
    MMMMMIHHHIHMMMMMHHHHHHHHMMHHHHHII::::.:'              ::::.
   :MMMMMIIHHHIHHHMMMMHHHHHHHHHHHHIIII::::.''          ....::::.
   IMMMMHHIIIHHIIHHHHMMMHHHHHHHHIHHHHHII::.         ....  ...:::.
   IMMMHHHIHIIIIIIIHHMMMHHHHHHHHHIIIII:::..                ....::.
   IMMHHHHHI::IIIHHIHHMMMHHHHHHHII::::::.....  .              ...:.
   :MMMMHHIII::IHHHHHIHHMMMHHHHHHII:::::..   ..    ,      ...   ..:.
   IMMHHHHII:' '' ':HMHHHHMMMHHHHHII:::..::''     .             ..::
   HMMHHHII::'    :::.HHHHHHMMMHHHHHII::''   ..     ..         ....::
   HHMHHHH...    ....::HHHMHMMMMMHHHIII:::''..   ...            ....:.
   HMHHHII:''    ''''::IHHMMHMMMMIHHHHHH::.  ....  .  .    ..    ...::.
   MMHHHI::'    .. ... IHHHHMMMM  'IHHHHII::...... ....            ..::
   MMMHHH::       '':::HHHHMHMM'    'HHHHI::::::.... .               ...
   MMMIHI:: :       :,:.MHMHMMM       'HHHH::::..........             ..
   MMMMHIIH:.         ..HHHMMM'        'HMHHHHI::,,,,..          ...
  ,MMMHHH::.    ..   ...:HHMM'           'MMMHHHI:::....  ...        ..
  IMMMMHHH::.     ....:::MMMI              IMMMHHHH:::......  ..
 .HMMMMHHH::...   ..  ..:MMM       ....::II.IIMMMHHHMH::::.......
 MMMMMMMMHHH::..  ..::HHMMM   ,:IIIHIIII:IIIHHMMMMMMMMHHH:::.. .
- MMMMHHHHHIII::.  .:HMMMMM:IIIIH:'''':'':''::::IHMMMMHHHH::........
 M MMMMHHIII::''IHHHIIIIIHHHI:''             '':::.IHMMMMMHHHH::.....
H HHMMHIIHIIHHHIII::::''''''                   '':::IHMMMMHHMHHI:::...
I II''HHHHIII:'::...   ..                      ....  .HHHMMHMMMMHHI::..
H HHIII:''''':...     .              .....    :::: .IIHMHHHHHMHHHIMMH:..
I :'':::..         .         ....::::::: .::::::IIHHIIIHMHHIIIHHHMMMHHII
 .   .           .          ......::::::::'' IIHHHMHHHHHHHMMMMHHHMMMMMMM
     .....       ........::::::::::III::IIHHHHHHMHHHHHHHMMMMMMMMMMMMMMMM
                  ...........IIIHHHHHMMMMMMMMMMMMMMMMMMMMHHMMMMMMHII::'
 :.    . .. ...::::::::::IIIHHHHHHMMMMMMMMMMHHHHHMMMMMMMMMMHHMII::'''
. : : : IIHHHHHHHHHHMMMMMMMMMMMMMMMMMMMHHHHHIIII::'''''''
 . . :HHHHMMMMMMHHIII:::::::::::::'''''''''
. . :HHHHHHHHHHHHHHH'''''''
.:HIIIIIII''''
        """
    elif __moo_iter == 1:
        print """
                               .::::.
                             .::::::::.
                             :::::::::::
                             ':::::::::::.. 
                              :::::::::::::::'
                               ':::::::::::.
                                 .::::::::::::::'
                               .:::::::::::...
                              ::::::::::::::''
                  .:::.       '::::::::''::::
                .::::::::.      ':::::'  '::::
               .::::':::::::.    :::::    '::::.
             .:::::' ':::::::::. :::::      ':::.
           .:::::'     ':::::::::.:::::       '::.
         .::::''         '::::::::::::::       '::.
        .::''              '::::::::::::         :::...
     ..::::                  ':::::::::'        .:' ''''
  ..''''':'                    ':::::.'
        """
    elif __moo_iter == 2:
        print """
________________________________________m8888888
___________________________________mMoooooooM8888
_________________________________MogggooooooM88888
___________________________MMMMMoooooooooooM8888888
___________________________M6ooooMMMmoooooooM888888888
________________________Mmooo8oooooooooooooM88888888888
_______________________MmmmooooooooooooooM88888888888888
______________________Moooooooooo8888888M8888888888888888
_____________________Mooooooooooooo88888M88888888888888888
______________________MmooooooooooooooommM88888888888888888
__________________________M88ooooo888mooMM88888888888888888
___________________________M88888888oommooM88888888888888888
____________________________M888888ooooMM8888888888888888888
____________________________MooooooooooM888888888888888888888
_________________________888MoooooooooM8888888888888888888888
______________________888888MooooooooM88888888888888888888888
_____________________88888888MoooooooM8888888888mmmm888888888
____________________888888888Mo8oooooM8888888MooooooooM888888
___________________8888888888Moo8oooM8888MM8ooooooooooooM88888
___________________8888888888Mooo88ooooM888MoooooooooooooM8888
____________________M8o8888ooo8oo88ooo0ooMMoo888oooooooooooM88
___________________Mooo88888ooo8o88o8oooooooooo8888oooooooooM8
___________________Moo8888o8ooooo8ooooooooooooooo8888ooooooooM8
___________________Mooo88oooooooooooooooooooooooo888888oooooooM8
___________________Mooooooooooooooooooooooooooooo88888888ooooooM8
____________________MooMooooooooooooooooooooooooooM888ooo88oooooM
_____________________Mmoooooooooooooooooooooooooo888Moooo8oooooooM
______________________Moooooooooo8oooooooooooooo8888MMooooooooooooM
_______________________Moooooooo88ooooooooooooo88888MMM8oooooooooooM
_______________________Moooooooo88oooooooooooooo88888MMMMoooooooooooM
_______________________Moooooooo88Moooooooooooooooo88888MMMMoooooooooM
______________________Mooooooooo88Moooooooooooooooo8MooooMMMMoooooooooM
_____________________Mooooooooo8MMooooooooooooooo88MoooooMMMMooooooooooM
____________________Mooooooooo88MMoom888mooooooo88MooooooMM_MMooooooooooM
____________________M8moooooo888MMoom@@8moooo8888M8oooooooMM__MMoooooooooM
___________________M@88moooo888MooMom8@8mooo8888MoooooooooMM___Mmoooooo000M
____________________*M8mooo8888MooooMm8mooo888M888ooooooooMM___Moooooo00000M
_______________________MMMMMM8888oooooMMmmmmM88888oooooooooMM_Moooooooo0008M
_____________________________M88Moooooo8888888888oooooooooooMMoooooooooo88M
_____________________________M88Mooooo8o888888888ooooooooooooMoooooooo888M
______________________________M88Mooooo8ooo888888oooooooooooMooooooo8888M
_______________________________M888Mooo888ooooo888ooooooooooMoooooo8888M
_______________________________M88888Moo888oooooo8888ooooooMooooooo888M88M
________________________________M888888Mo8888oooooo8888oooMooooooo888M88888M
_________________________________M8888888Mo8888ooooooooooMoooooooo88M88888888M
___________________________________M888888M88888oooooooooMoooooooo8M88888888888M
____________________________________M8oo888M888888ooooooMoooooooo8M888888oooo888M
_____________________________________M8ooooMM88888888ooMooooooooM8888oooooooooooo8M
______________________________________MooooM_M88888888MooooooooM888ooooooooooooooo8M
_______________________________________MooooM_M888888Mooooooo8M88**ooooooooooooooo88M
________________________________________MooooM_mmmmmmMoooooo8Mmooooooooooooooooooo888M
_________________________________________MoooQooommmmMoooMMooooooooooooooooooooooo888M
________________________________________MM88ooo8ooooMMMoooooooooooooooooooooooooo8888M
_____________________________________mM8888M88o88mMmoooooooooooooooooooooooooooo88888M
_______________________________mMMMoooooooooM888Mmooooooooooooooooooooooooooooo888888M
__________________________MMMMoooooooooooooooMMooooooooooooooooooooooooooooooo888888M
______________________MMMoooooooooooooooooMMooooooooooooooooooooooooooooooo88888888M
___________________MMMooooooooooooooooooMMooooooooooooooooooooooooooooo88888888888M
________________MMooooooooooooooooooooMMooooooooooooooooooooooooooooo8888888888M
_____________MMoooooooooooooooooooooMMooooooooooooooooooooooooooo888888888888MMM
___________MmoooooooooooooooooooooMMoooooooooooooooooooooooooo888888888888M88888M
_________MooooooooooooooooooooooMooooooooooooooooooooooooooo88888888888MM_M8888888M
_______MoooooooooooooooooooooooMooooooooooooooooooooooooo8888888888M_____M8888888888M
______M8ooooooooooooooooooo88Mooooooooooooooooooooooo88888888888M_______M8888888888888M
______M88oooooooooooo8888888Moooooooooooooooooooooo888888MMMMMMMMMMMM888888888888888888888M
______M8888ooooooo88888MMMMMooooooooooooooooooooo8888M888888888888888888888888888888888888888M
_______M888888888888MMM888Moooooooooooooooooooo88M8ooooooooooo8888888888888888888888MMMMMMMMMMMM
________M888888888888oooooMoooooooooooooooooooMMoooooo8888888888888888888888MMM
_________M8888888888888888M8888oooooo88ooooooMoo888888888888888888888MM
____________MMMMMMMMMMMMMMM888888ooo88888oo8Mo888888888888888888MM
_____________________________M8888888888888Mo888888888888MMM
_______________________________M88888888888MMMMMMM
__________________________________MMMMM
        """
    elif __moo_iter == 3:
        print """
_________________________8888  8888888
__________________888888888888888888888888
_______________8888ooo8888888888888888888888888
_____________8888oooooo8888888888888888888888888888
____________88oooooooo888ooo8888888888888888888888888
__________88888888oooo8ooooooooooo88888888888888888888
________888_8oo888888oooooooooooooooooo88888888888 888
___________88oooo88888888oooomoooooooooo88888888888 8
_________888888888888888888oMooooooooooo8888888888888
________88888888888888888888ooooooooooooM88888888888888
________8888888888888888888888oooooooooM8888888888888888
_________8888888888888888888888oooooooM888888888888888888
________8888888888888888oo88888ooooooM88888888888888888888
______88888888888888888ooo88888oooooM888888888888888 8888
_____88888888888888888ooo88888ooooMoo;o*M*o;888888888 88
____88888888888888888ooo8888oooooMooooooooooo88888888 8
___88888888888888888oooo88ooooooMo;ooooooooooo888888888
__8888888888888888888ooo8ooooooMooaAaooooooooM8888888888_______
__88___8888888888oo88oooo8ooooMooooooooooooo888888888888888_8888
_88__88888888888ooo8oooooooooMoooooooooo;oo88o88888888888888888
_8__8888888888888oooooooooooMoo\"@@@@@\"oooo8w8888888888888888
__88888888888o888ooooooooooMooooo\"@a@\"oooooM8i888888888888888
_8888888888oooo88oooooooooM88oooooooooooooM88z88888888888888888
8888888888ooooo8oooooooooM88888oooooooooMM888!888888888888888888
888888888ooooo8oooooooooM8888888MAmmmAMVMM888*88888888___88888888
888888_MoooooooooooooooM888888888oooooooMM88888888888888___8888888
8888___MooooooooooooooM88888888888ooooooMM888888888888888____88888
_888___MoooooooooooooM8888888888888MooooomM888888888888888____8888
__888__MooooooooooooM8888o888888888888oooomooMm88888_888888___8888
___88__Moooooooooooo8888o88888888888888888ooooooMm8___88888___888
___88__Moooooooooo8888Moo88888oo888888888888oooooooMm88888____88
___8___MMoooooooo8888Mooo8888ooooo888888888888ooooooooMm8_____8
_______8Mooooooo8888Mooooo888ooooooo88ooo8888888ooooooooMm____8
______88MMooooo8888Mooooooo88oooooooo8ooooo888888oooMoooooM
_____8888Mooooo888MMoooooooo8oooooooooooMoooo8888ooooMooooM
____88888Mooooo88oMoooooooooo8oooooooooooMooo8888ooooooMooM
___88_888MMooo888oMoooooooooooooooooooooooMo8888oooooooooMo
___8_88888Mooo88ooMoooooooooooooooooooooooMMo88ooooooooooooM
_____88888Mooo88ooMoooooooooo*88*ooooooooooMo88ooooooooooooooM
____888888Mooo88ooMooooooooo88@@88ooooooooMoo88ooooooooooooooM
____888888MMoo88ooMMoooooooo88@@88oooooooMooo8ooooooooooooooo*8
____88888__Mooo8ooMMooooooooo*88*ooooooooooMooooooooooooooooo88@@
____8888___MMooooooMMoooooooooooooooooooooMMooooooooooooooooo88@@
_____888____MoooooooMMoooooooooooooooooooMMooMooooooooooooooooo*8
_____888____MMoooooooMMMooooooooooooooooMMoooMMoooooooooooooooM
______88_____MooooooooMMMMoooooooooooMMMMoooooMMooooooooooooMM
_______88____MMoooooooooMMMMMMMMMMMMMooooooooMMMooooooooMM
________88____MMooooooooooooMMMMMMMooooooooooooMMMMMMMMMM
_________88___8MMooooooooooooooooooooooooooooooooooMMMMMM
__________8___88MMooooooooooooooooooooooMoooMooooooooMM
______________888MMooooooooooooooooooMMooooooMMooooooMM
_____________88888MMoooooooooooooooMMMooooooomMoooooMM
_____________888888MMoooooooooooooMMMoooooooooMMMoooM
____________88888888MMoooooooooooMMMoooooooooooMMoooM
___________88_8888888MoooooooooMMMooooooooooooooMoooM
___________8__888888_MoooooooMMoooooooooooooooooMoooMo
______________888888_MooooooMoooooooooooooooooooMoooMM
_____________888888__MoooooMooooooooooooooooooooooooMoM
_____________888888__MoooooMooooooooo@ooooooooooooooMooM
_____________88888___Moooooooooooooo@@oooooooooooooooMooM
____________88888___Moooooooooooooo@@@ooooooooooooooooMooM
___________88888___Mooooooooooooooo@@ooooooooooooooooooMooM
__________88888___Mooooomoooooooooo@ooooooooooMmoooooooMoooM
__________8888___MoooooMoooooooooooooooooooooooMMoooooooMoooM
_________8888___MoooooMoooooooooooooooooooooooMMMooooooooMoooM
________888____MoooooMmooooooooooooooooooooooMMMoooooooooMooooM
______8888____MMooooMmoooooooooooooooooooooMMMMooooooooomoomoooM
_____888______MoooooMooooooooooooooooooooMMMooooooooooooMoommoooM
__8888_______MMoooooooooooooooooooooooooMMooooooooooooomMooMMoooMo
_____________MoooooooooooooooooooooooooMooooooooooooooomMooMMoooMm
____________MMoooooomoooooooooooooooooooooooooooooooooooMooMMoooMM
____________MooooooooMoooooooooooooooooooooooooooooooooooMooMoooMM
___________MMoooooooooMoooooooooooooMoooooooooooooooooooooMoMoooMM
___________MoooooooooooM88oooooooooMoooooooooooooooooooooooMMooMMM
___________Moooooooooooo8888888888MooooooooooooooooooooooooMMooMM
___________Mooooooooooooo88888888MoooooooooooooooooooooooooMooMM
___________Moooooooooooooo888888MoooooooooooooooooooooooooMooMM
___________Mooooooooooooooo88888MoooooooooooooooooooooooooMoMM
___________Mooooooooooooooooo88MooooooooooooooooooooooooooMMM
___________MoooooooooooooooooooMooooooooooooooooooooooooooMMM
___________MMoooooooooooooooooMooooooooooooooooooooooooooMMM
____________MoooooooooooooooooMooooooooooooooooooooooooooMMM
____________MMoooooooooooooooMooooooooooooooooooooooooooMMM
_____________MoooooooooooooooMoooooooooooooooooooooooooMMM
_____________MMoooooooooooooMoooooooooooooooooooooooooMMM
______________MoooooooooooooMooooooooooooooooooooooooMMM
______________MMoooooooooooMooooooooooooooooooooooooMMM
_______________MoooooooooooMoooooooooooooooooooooooMMM
_______________MMoooooooooMoooooooooooooooooooooooMMM
________________MoooooooooMooooooooooooooooooooooMMM
________________MMoooooooMooooooooooooooooooooooMMM
_________________MMooooooMoooooooooooooooooooooMMM
_________________MMoooooMoooooooooooooooooooooMMM
__________________MMooooMooooooooooooooooooooMMM
__________________MMoooMooooooooooooooooooooMMM
___________________MMooMoooooooooooooooooooMMM
___________________MMoMoooooooooooooooooooMMM
____________________MMMooooooooooooooooooMMM
____________________MMooooooooooooooooooMMM
_____________________MoooooooooooooooooMMM
____________________MMooooooooooooooooMMM
____________________MMoooooooooooooooMMM
____________________MMooooMoooooooooMMMo
____________________mMMooooMMoooooooMMMM
_____________________MMMoooooooooooMMMoM
_____________________mMMoooMoooooooMoMoM
______________________MMooMMMMoooooooMoM
______________________MMooMMMooooooooMoM
______________________mMMooMMooooooooMoM
_______________________MMooMMoooooooooMoM
_______________________MMooMMooooooooooMom
_______________________MMoooMoooooooooooMM
_______________________MMoooMoooooooooooMM
_______________________MMMoooooooooooooooMo
_______________________MMMoooooooooooooooMo
_______________________MMMooooooooooooooooM
_______________________MMMooooooooooooooooM
_______________________MMMooooooooooooooooMm
________________________MMooooooooooooooooMM
________________________MMMoooooooooooooooMM
________________________MMMoooooooooooooooMM
________________________MMMoooooooooooooooMM
________________________MMMoooooooooooooooMM
_________________________MMooooooooooooooMMM
_________________________MMMoooooooooooooMM
_________________________MMMoooooooooooooMM
_________________________MMMooooooooooooMM
__________________________MMooooooooooooMM
__________________________MMooooooooooooMM
__________________________MMoooooooooooMM
__________________________MMMooooooooooMM
__________________________MMMooooooooooMM
___________________________MMoooooooooMM
___________________________MMMooooooooMM
___________________________MMMooooooooMM
____________________________MMooooooooMM
____________________________MMMooooooMM
____________________________MMMooooooMM
_____________________________MMooooooMM
_____________________________MMooooooMM
______________________________MMoooooMM
______________________________MMoooooMMo
______________________________MMoooooMoM
______________________________MMoooooMoM
______________________________oMooooooMo
_____________________________MoMoooooooM
____________________________MoooMooooooM
___________________________MooooMooooooM
__________________________MoooooMoooooooM
_________________________MooooooMMoooooooM
_________________________MoooooooMooooooooM
_________________________M;o;ooooMoooooooooM
_________________________Momo;oooMooooooooooM
_________________________MMomomooMoooooooo;oM
__________________________MMomooMMooooooo;o;M
___________________________MMooMMMoooooo;omoM
___________________________MMMM_MMoooomomoMM
__________________________________MMoooomoMM
___________________________________MMooooMM
_____________________________________MMMMM
        """
    else:
        print """
.................0..l..0.................
..............0.....l.....0..............
.............0.............0.............
............0...............0............
............0...............0............
.............0.0.0.0.0.0.0.0.............
..............0...........0..............
..............0...........0..............
..............0...........0..............
..............0...........0..............
..............0...........0..............
..............0...........0..............
..............0...........0..............
..............0...........0..............
..............0...........0..............
..............0...........0..............
..............0...........0..............
..............0...........0..............
..............0...........0..............
......0..0....0...........0....0..0......
...0........0.0...........0.0........0...
.0...........00...........00...........0.
0.......................................0
0.......................................0
0.......................................0
.0.....................................0.
        """
    __moo_iter+=1

