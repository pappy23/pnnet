//Moo.cpp

#include "Includes/Std.h"

#include "Moo.h"

namespace pann {
    void
    moo()
    {
        #ifdef OPTION_ENABLE_MOO_DEFINED
        static int pic = 2;

        std::cout<<"++++++++++++++++++++++++++++++++ S M I L E :-D +++++++++++++++++++++++++++\n";
        if(pic == 2) {
            std::cout<<
                "         .:IHHMHHI:..,\n"
                "  . :HI..IIHHMMMHIHHH:..\n"
                " . : H:HMHHMMMMMHMMHMHI::,\n"
                " I:HMHMHMHHHMMMMMMMMMH::..:\n"
                ": M:MMMMMHMMMMMMHMMMMMMMMMI:\n"
                " M MMMMMMMMMHMMHMMMMMMMMMM,:\n"
                ": M:MMMMMMMMMMMMMMMMMMMMMMM,\n"
                " H:H:MMMMMMMMHMMMMHHMMMMMM:..\n"
                "  M:MMMHMMMMMMHHMMMMMMMMMMMMM\n"
                " :M:M:M:MHMMHHHI'  '::I HMMMMMI\n"
                ": M:M:MMMMMMMMHHI, '   HIHMMMMMM.\n"
                " M:M:M:MMMMMMMIII,     '':IHMMMM\n"
                ": M:MMMMMHMMMMMMH:      ... HMMM:\n"
                " M:M:MMMMMMMMMMHHH        IMM MH,\n"
                "M MMMMMMMMMMMMMMMI,   ...IMMMMMM\n"
                " M:MMMHMMMMMMMMMMM      :MIMMI.,\n"
                ": M:MMMHHMMMMMMMM IMMI..  IMMIHH:.\n"
                " M:MMMMHHHHHMMMMIMMH:::... 'IHI,...\n"
                "M MMMMMMMMMMMMM'H:MHIII:...:  ':.:.\n"
                " M:MMHHMMHHMHI ,,MMMII:'::I:I.  :I::\n"
                "M MMMMMMMHH....:'''''::.::I,.: MII:\n"
                " M:MMMMMM::.::'''   '':::IH:IM:: IM.\n"
                "M MMMMMMMMII:'' '    ''::I::  :MMMM.\n"
                " M:MMMMMMMII:.        ':I:.,MMMMM':\n"
                ": M:MMMMMHHHII:.     .::I:IIMMM':::\n"
                " M:M:MMMMMMMMII::.. .:II: '::II:''.,:''''::..,\n"
                ": M:MMMMMMMMMMI:::.:I::.. .. ..:'' ,.:'''::,   ':,\n"
                " .:M:MMMMMMHII::'II::....' .:'                   ::.,\n"
                "  , M:MMMMMMMMMMHI::....::::: :'        ::           '.\n"
                "    : H:MMMMMMMHHHHHI:..::::II::' .::::::III:,,         ',\n"
                "      'IHMMMHHHHHHIHIIIIHHHH:    ,'' ::,   .::..          '',\n"
                "         'MMMHHHHHIIHHHHHHHII: .:::    ::::::::......   ....:,\n"
                "          MMHHHHHHHIHIIHHIIII  '...''''   '''H:IIHII...    ...',\n"
                "         .MMHHHHHHHHHHIIIIII':' .....    .:::::II.  'HHH:..   .. ,\n"
                "        .MMMMMHHHHII::'''  ''       ..     .....:HI:,  II:..  ...::\n"
                "       ,MHMMMMMHH:.''      ...            ..   ...::H:,  'I::.    .:\n"
                "      .IMHMMMHI:''     ..:. I       ..    ..    ...::II,  'II....   ::\n"
                "      IMHIMMI:''         . :                      ....::H:  I:: .    ..\n"
                "      MMHIMMI:.''    ..:    ...:            ...      ....II,'I:....    .\n"
                "     'MMHIMM:'':.    .         .. .     .. ,:           ,.IIHI:::.\n"
                "     IMIHMMI:::''           .     ,                  .,,  ..::IHIII..\n"
                "     IMIHMMM.......                .                         ..::HH:..\n"
                "     HMIHMMMH:.       .                                    ...:::IIHI .\n"
                "     IHIMMM::...                                              '''::::: .\n"
                "     :MMHMM:..  .       ...       I II..... .                     ' ' ::\n"
                "     'MIHMMI:...       :::..    .     I. :::::.. ...::....  ..         ' ' \n"
                "      MMHMMM:...  ..         .:.....:.III:::.........::::........   ..\n"
                "      HMIMMI:...         ..:::::::::III:H:IIHII:::::...::::.........\n"
                "      IMHIMM:.....         ....:::::III:IIIHHHHHHH'III:....:..........\n"
                "      'MHHMM:...           ....:::::IIIIHMI:':::IHHMHIII:::::..........\n"
                "       IMIMM:::...            ...:::::III' :....::::IHHMHIIII.::.:.... .\n"
                "       'MMIMM:...             ....::I:.'  '      ''''::IIIHMH,':::::::: ..\n"
                "        IMHMMI:::....       ,    ..::::::..    .. ...   ..::IHMM:,'''::;;:. .\n"
                "         HMMMMH......:  .         ..::::::..            ..::::MMMM)\n"
                "         IMIMMHH:...:...     ..  ...:::::...   ..  ...  ..:,::MMMI\n"
                "          HMHMMHI:... ..:.       ....:::::::..:.      ....::::IMM'\n"
                "          'MMHHHHI:..::...     ....::::II::.::....  ..: ...::IHM'\n"
                "           IMMHHI:.:::... .      ......::III:..::.::::::..IIHHM'\n"
                "           'MMMHI:::..::.       ......:IIIHIHII::IHHHHHHHHHI''\n"
                "            MIMHHHII::..:.    .. ..:::I::.:HHHHIHMMMHMHHIH'\n"
                "            'MMHHHHII::. ...        ..:.::HHHHHHHMHHMMHI'\n"
                "             IMMHHIII:::...       .....IHHIIHHIIIHHHHMH\n"
                "             'MMHHHIII:..:..   ..  ...:HI:...:::IIHHHMH\n"
                "              IMHHHII::::...       ..IHI..  ..:HHHIHMHH\n"
                "              'MHHII:::....       ...III:...  .IHHHHMMH\n"
                "               IMHHHIII::...    ..  ..IHH..  ..:::IHHMH\n"
                "               'MHHHIIIII:... .    ....II:....:::IHMMHI\n"
                "                MHHIIII:::::.        ...:::..:::.HHHHH'\n"
                "                'MMHI::::.......       ..:::::.IHHHIHH\n"
                "                 MMIII::::.......    ....::::::HIIHHH'\n"
                "                 'MHHHHHII::...         ...:::::MHHHH\n"
                "                  MHHHHHHIIH::.           .::::HIMMH'\n"
                "                  HMHHHHHHHHH::..       ....:::HHHHI\n"
                "                  IMMHHHHHIIII:.    ..   ..::::IHHM'\n"
                "                  IMMHHHHHHHHHI::.    ..  ..::HMHHH\n"
                "                  IMHHHHHHHIII::....   ......::HHHI\n"
                "                  HMHHHHHHIII::''' '   '''''::MHHM'\n"
                "                 IMMHHHIII::'''            '::HMMM\n"
                "                ,HMHHHII::''''         ''''::MMMHM\n"
                "               IHMHHHHH:''   ''        ''':IHMMMMI\n"
                "              ,HMHHHHII::.            ''..::MMMMM'\n"
                "             ,HMHHII::''          ''''':HHHIHMMMM\n"
                "            ,HMHHI::.              ''::IIIMMHHMMM\n"
                "          ,IHMMH::''               ..''IHIIMMHMMH\n"
                "         ,HMHHI:''              ...   .IIIHIMHMHH\n"
                "        ,HMMI:'          .        ...   ::H MMHHI\n"
                "       :HMHI:'           ..   ... ....:::. MMMHH'\n"
                "      IHMHHHI:     .         ...  ....:::::MMHIM\n"
                "    ,IHMHHHHII::.             .....  ....::::MM'\n"
                "   ,HMMHHHHII::.                     ....:::MH'\n"
                "   HMHHHHHHII:::.        ......     ...:::..IM'\n"
                "  MMMHHHHIII::,             ....::..   ..:::M'\n"
                " :MHHHHHIII::'                ....::..:::.:IM'\n"
                " MMHHHHHIII::'                ....::::.::IHM'\n"
                ",MIHHHHHHHII.  .                   :::. .:III\n"
                "IMIHHHHMMHHII                     ''::::::II:,\n"
                "HMIHHMMHHHHH::.                 '' :::IIH::,:,\n"
                "MMHHHHHHHII::'                    ''::::::II::,\n"
                "HMHHHHHHHHHI:'          ..       ..:   :::::....\n"
                "IMMHHHHHHHHH::..                  ...:::::..:II::.\n"
                "'MMHHHHHHHHH::::.          ....    ....::::.::I::.,\n"
                " IMMIHHHHHHHHHII::.              ....::::::...:::::.\n"
                " 'MMMHHHHHHHHHHII::.           ...    ........::::::,\n"
                "  HMMMHHHHHHHHHIIII::.        ....:::.   ....::::..:..\n"
                "  'HMMMHHHHHHHHHHIII:::.,       ,,:          ...::..:,.\n"
                "    MMHMMHHHHHHHHIIII::::...      ...:.     ..  ...::::.\n"
                "    MMHHMMMHHHHHHHHHHHHHI::...                  ......::.\n"
                "    MMMIHHMMMHHHHHHHHIIIII:::...     ...:             ...:\n"
                "    MMMMIHMMMMMMHHHMHHHHHHHIIII:::...::            .....::.\n"
                "    MMMMMIHMMMMHHHHMHHHHMHHH::.I:..          ...      ....:.\n"
                "    MMMIHHIHHHMMHHHHMMMHHHHHMMHH::.   ...         ....  ..::.\n"
                "    MMMMHHHIHHHHMHHHHHHMMMHHHHHHIII:::..,         ....  ...::.\n"
                "    MMMMMIHHHIHMMMMMHHHHHHHHMMHHHHHII::::.:'              ::::.\n"
                "   :MMMMMIIHHHIHHHMMMMHHHHHHHHHHHHIIII::::.''          ....::::.\n"
                "   IMMMMHHIIIHHIIHHHHMMMHHHHHHHHIHHHHHII::.         ....  ...:::.\n"
                "   IMMMHHHIHIIIIIIIHHMMMHHHHHHHHHIIIII:::..                ....::.\n"
                "   IMMHHHHHI::IIIHHIHHMMMHHHHHHHII::::::.....  .              ...:.\n"
                "   :MMMMHHIII::IHHHHHIHHMMMHHHHHHII:::::..   ..    ,      ...   ..:.\n"
                "   IMMHHHHII:' '' ':HMHHHHMMMHHHHHII:::..::''     .             ..::\n"
                "   HMMHHHII::'    :::.HHHHHHMMMHHHHHII::''   ..     ..         ....::\n"
                "   HHMHHHH...    ....::HHHMHMMMMMHHHIII:::''..   ...            ....:.\n"
                "   HMHHHII:''    ''''::IHHMMHMMMMIHHHHHH::.  ....  .  .    ..    ...::.\n"
                "   MMHHHI::'    .. ... IHHHHMMMM  'IHHHHII::...... ....            ..::\n"
                "   MMMHHH::       '':::HHHHMHMM'    'HHHHI::::::.... .               ...\n"
                "   MMMIHI:: :       :,:.MHMHMMM       'HHHH::::..........             ..\n"
                "   MMMMHIIH:.         ..HHHMMM'        'HMHHHHI::,,,,..          ...\n"
                "  ,MMMHHH::.    ..   ...:HHMM'           'MMMHHHI:::....  ...        ..\n"
                "  IMMMMHHH::.     ....:::MMMI              IMMMHHHH:::......  ..\n"
                " .HMMMMHHH::...   ..  ..:MMM       ....::II.IIMMMHHHMH::::.......\n"
                " MMMMMMMMHHH::..  ..::HHMMM   ,:IIIHIIII:IIIHHMMMMMMMMHHH:::.. .\n"
                "- MMMMHHHHHIII::.  .:HMMMMM:IIIIH:'''':'':''::::IHMMMMHHHH::........\n"
                " M MMMMHHIII::''IHHHIIIIIHHHI:''             '':::.IHMMMMMHHHH::.....\n"
                "H HHMMHIIHIIHHHIII::::''''''                   '':::IHMMMMHHMHHI:::...\n"
                "I II''HHHHIII:'::...   ..                      ....  .HHHMMHMMMMHHI::..\n"
                "H HHIII:''''':...     .              .....    :::: .IIHMHHHHHMHHHIMMH:..\n"
                "I :'':::..         .         ....::::::: .::::::IIHHIIIHMHHIIIHHHMMMHHII\n"
                " .   .           .          ......::::::::'' IIHHHMHHHHHHHMMMMHHHMMMMMMM\n"
                "     .....       ........::::::::::III::IIHHHHHHMHHHHHHHMMMMMMMMMMMMMMMM\n"
                "                  ...........IIIHHHHHMMMMMMMMMMMMMMMMMMMMHHMMMMMMHII::'\n"
                " :.    . .. ...::::::::::IIIHHHHHHMMMMMMMMMMHHHHHMMMMMMMMMMHHMII::'''\n"
                ". : : : IIHHHHHHHHHHMMMMMMMMMMMMMMMMMMMHHHHHIIII::'''''''\n"
                " . . :HHHHMMMMMMHHIII:::::::::::::'''''''''\n"
                ". . :HHHHHHHHHHHHHHH'''''''\n"
                ".:HIIIIIII''''\n"
                "\n"
                ;
        } else if(pic == 3) {
            std::cout<<
                "                                  .::::.\n"
                "                                .::::::::.\n"
                "                                :::::::::::\n"
                "                                ':::::::::::.. \n"
                "                                 :::::::::::::::'\n"
                "                                  ':::::::::::.\n"
                "                                    .::::::::::::::'\n"
                "                                  .:::::::::::...\n"
                "                                 ::::::::::::::''\n"
                "                     .:::.       '::::::::''::::\n"
                "                   .::::::::.      ':::::'  '::::\n"
                "                  .::::':::::::.    :::::    '::::.\n"
                "                .:::::' ':::::::::. :::::      ':::.\n"
                "              .:::::'     ':::::::::.:::::       '::.\n"
                "            .::::''         '::::::::::::::       '::.\n"
                "           .::''              '::::::::::::         :::...\n"
                "        ..::::                  ':::::::::'        .:' ''''\n"
                "     ..''''':'                    ':::::.'\n"
                ;
        } else if(pic == 4) {
            std::cout<<
                "________________________________________m8888888\n"
                "___________________________________mMoooooooM8888\n"
                "_________________________________MogggooooooM88888\n"
                "___________________________MMMMMoooooooooooM8888888\n"
                "___________________________M6ooooMMMmoooooooM888888888\n"
                "________________________Mmooo8oooooooooooooM88888888888\n"
                "_______________________MmmmooooooooooooooM88888888888888\n"
                "______________________Moooooooooo8888888M8888888888888888\n"
                "_____________________Mooooooooooooo88888M88888888888888888\n"
                "______________________MmooooooooooooooommM88888888888888888\n"
                "__________________________M88ooooo888mooMM88888888888888888\n"
                "___________________________M88888888oommooM88888888888888888\n"
                "____________________________M888888ooooMM8888888888888888888\n"
                "____________________________MooooooooooM888888888888888888888\n"
                "_________________________888MoooooooooM8888888888888888888888\n"
                "______________________888888MooooooooM88888888888888888888888\n"
                "_____________________88888888MoooooooM8888888888mmmm888888888\n"
                "____________________888888888Mo8oooooM8888888MooooooooM888888\n"
                "___________________8888888888Moo8oooM8888MM8ooooooooooooM88888\n"
                "___________________8888888888Mooo88ooooM888MoooooooooooooM8888\n"
                "____________________M8o8888ooo8oo88ooo0ooMMoo888oooooooooooM88\n"
                "___________________Mooo88888ooo8o88o8oooooooooo8888oooooooooM8\n"
                "___________________Moo8888o8ooooo8ooooooooooooooo8888ooooooooM8\n"
                "___________________Mooo88oooooooooooooooooooooooo888888oooooooM8\n"
                "___________________Mooooooooooooooooooooooooooooo88888888ooooooM8\n"
                "____________________MooMooooooooooooooooooooooooooM888ooo88oooooM\n"
                "_____________________Mmoooooooooooooooooooooooooo888Moooo8oooooooM\n"
                "______________________Moooooooooo8oooooooooooooo8888MMooooooooooooM\n"
                "_______________________Moooooooo88ooooooooooooo88888MMM8oooooooooooM\n"
                "_______________________Moooooooo88oooooooooooooo88888MMMMoooooooooooM\n"
                "_______________________Moooooooo88Moooooooooooooooo88888MMMMoooooooooM\n"
                "______________________Mooooooooo88Moooooooooooooooo8MooooMMMMoooooooooM\n"
                "_____________________Mooooooooo8MMooooooooooooooo88MoooooMMMMooooooooooM\n"
                "____________________Mooooooooo88MMoom888mooooooo88MooooooMM_MMooooooooooM\n"
                "____________________M8moooooo888MMoom@@8moooo8888M8oooooooMM__MMoooooooooM\n"
                "___________________M@88moooo888MooMom8@8mooo8888MoooooooooMM___Mmoooooo000M\n"
                "____________________*M8mooo8888MooooMm8mooo888M888ooooooooMM___Moooooo00000M\n"
                "_______________________MMMMMM8888oooooMMmmmmM88888oooooooooMM_Moooooooo0008M\n"
                "_____________________________M88Moooooo8888888888oooooooooooMMoooooooooo88M\n"
                "_____________________________M88Mooooo8o888888888ooooooooooooMoooooooo888M\n"
                "______________________________M88Mooooo8ooo888888oooooooooooMooooooo8888M\n"
                "_______________________________M888Mooo888ooooo888ooooooooooMoooooo8888M\n"
                "_______________________________M88888Moo888oooooo8888ooooooMooooooo888M88M\n"
                "________________________________M888888Mo8888oooooo8888oooMooooooo888M88888M\n"
                "_________________________________M8888888Mo8888ooooooooooMoooooooo88M88888888M\n"
                "___________________________________M888888M88888oooooooooMoooooooo8M88888888888M\n"
                "____________________________________M8oo888M888888ooooooMoooooooo8M888888oooo888M\n"
                "_____________________________________M8ooooMM88888888ooMooooooooM8888oooooooooooo8M\n"
                "______________________________________MooooM_M88888888MooooooooM888ooooooooooooooo8M\n"
                "_______________________________________MooooM_M888888Mooooooo8M88**ooooooooooooooo88M\n"
                "________________________________________MooooM_mmmmmmMoooooo8Mmooooooooooooooooooo888M\n"
                "_________________________________________MoooQooommmmMoooMMooooooooooooooooooooooo888M\n"
                "________________________________________MM88ooo8ooooMMMoooooooooooooooooooooooooo8888M\n"
                "_____________________________________mM8888M88o88mMmoooooooooooooooooooooooooooo88888M\n"
                "_______________________________mMMMoooooooooM888Mmooooooooooooooooooooooooooooo888888M\n"
                "__________________________MMMMoooooooooooooooMMooooooooooooooooooooooooooooooo888888M\n"
                "______________________MMMoooooooooooooooooMMooooooooooooooooooooooooooooooo88888888M\n"
                "___________________MMMooooooooooooooooooMMooooooooooooooooooooooooooooo88888888888M\n"
                "________________MMooooooooooooooooooooMMooooooooooooooooooooooooooooo8888888888M\n"
                "_____________MMoooooooooooooooooooooMMooooooooooooooooooooooooooo888888888888MMM\n"
                "___________MmoooooooooooooooooooooMMoooooooooooooooooooooooooo888888888888M88888M\n"
                "_________MooooooooooooooooooooooMooooooooooooooooooooooooooo88888888888MM_M8888888M\n"
                "_______MoooooooooooooooooooooooMooooooooooooooooooooooooo8888888888M_____M8888888888M\n"
                "______M8ooooooooooooooooooo88Mooooooooooooooooooooooo88888888888M_______M8888888888888M\n"
                "______M88oooooooooooo8888888Moooooooooooooooooooooo888888MMMMMMMMMMMM888888888888888888888M\n"
                "______M8888ooooooo88888MMMMMooooooooooooooooooooo8888M888888888888888888888888888888888888888M\n"
                "_______M888888888888MMM888Moooooooooooooooooooo88M8ooooooooooo8888888888888888888888MMMMMMMMMMMM\n"
                "________M888888888888oooooMoooooooooooooooooooMMoooooo8888888888888888888888MMM\n"
                "_________M8888888888888888M8888oooooo88ooooooMoo888888888888888888888MM\n"
                "____________MMMMMMMMMMMMMMM888888ooo88888oo8Mo888888888888888888MM\n"
                "_____________________________M8888888888888Mo888888888888MMM\n"
                "_______________________________M88888888888MMMMMMM\n"
                "__________________________________MMMMM\n"
                ;
        } else if(pic == 5) {
            std::cout<<
                "_________________________8888  8888888\n"
                "__________________888888888888888888888888\n"
                "_______________8888ooo8888888888888888888888888\n"
                "_____________8888oooooo8888888888888888888888888888\n"
                "____________88oooooooo888ooo8888888888888888888888888\n"
                "__________88888888oooo8ooooooooooo88888888888888888888\n"
                "________888_8oo888888oooooooooooooooooo88888888888 888\n"
                "___________88oooo88888888oooomoooooooooo88888888888 8\n"
                "_________888888888888888888oMooooooooooo8888888888888\n"
                "________88888888888888888888ooooooooooooM88888888888888\n"
                "________8888888888888888888888oooooooooM8888888888888888\n"
                "_________8888888888888888888888oooooooM888888888888888888\n"
                "________8888888888888888oo88888ooooooM88888888888888888888\n"
                "______88888888888888888ooo88888oooooM888888888888888 8888\n"
                "_____88888888888888888ooo88888ooooMoo;o*M*o;888888888 88\n"
                "____88888888888888888ooo8888oooooMooooooooooo88888888 8\n"
                "___88888888888888888oooo88ooooooMo;ooooooooooo888888888\n"
                "__8888888888888888888ooo8ooooooMooaAaooooooooM8888888888_______\n"
                "__88___8888888888oo88oooo8ooooMooooooooooooo888888888888888_8888\n"
                "_88__88888888888ooo8oooooooooMoooooooooo;oo88o88888888888888888\n"
                "_8__8888888888888oooooooooooMoo\"@@@@@\"oooo8w8888888888888888\n"
                "__88888888888o888ooooooooooMooooo\"@a@\"oooooM8i888888888888888\n"
                "_8888888888oooo88oooooooooM88oooooooooooooM88z88888888888888888\n"
                "8888888888ooooo8oooooooooM88888oooooooooMM888!888888888888888888\n"
                "888888888ooooo8oooooooooM8888888MAmmmAMVMM888*88888888___88888888\n"
                "888888_MoooooooooooooooM888888888oooooooMM88888888888888___8888888\n"
                "8888___MooooooooooooooM88888888888ooooooMM888888888888888____88888\n"
                "_888___MoooooooooooooM8888888888888MooooomM888888888888888____8888\n"
                "__888__MooooooooooooM8888o888888888888oooomooMm88888_888888___8888\n"
                "___88__Moooooooooooo8888o88888888888888888ooooooMm8___88888___888\n"
                "___88__Moooooooooo8888Moo88888oo888888888888oooooooMm88888____88\n"
                "___8___MMoooooooo8888Mooo8888ooooo888888888888ooooooooMm8_____8\n"
                "_______8Mooooooo8888Mooooo888ooooooo88ooo8888888ooooooooMm____8\n"
                "______88MMooooo8888Mooooooo88oooooooo8ooooo888888oooMoooooM\n"
                "_____8888Mooooo888MMoooooooo8oooooooooooMoooo8888ooooMooooM\n"
                "____88888Mooooo88oMoooooooooo8oooooooooooMooo8888ooooooMooM\n"
                "___88_888MMooo888oMoooooooooooooooooooooooMo8888oooooooooMo\n"
                "___8_88888Mooo88ooMoooooooooooooooooooooooMMo88ooooooooooooM\n"
                "_____88888Mooo88ooMoooooooooo*88*ooooooooooMo88ooooooooooooooM\n"
                "____888888Mooo88ooMooooooooo88@@88ooooooooMoo88ooooooooooooooM\n"
                "____888888MMoo88ooMMoooooooo88@@88oooooooMooo8ooooooooooooooo*8\n"
                "____88888__Mooo8ooMMooooooooo*88*ooooooooooMooooooooooooooooo88@@\n"
                "____8888___MMooooooMMoooooooooooooooooooooMMooooooooooooooooo88@@\n"
                "_____888____MoooooooMMoooooooooooooooooooMMooMooooooooooooooooo*8\n"
                "_____888____MMoooooooMMMooooooooooooooooMMoooMMoooooooooooooooM\n"
                "______88_____MooooooooMMMMoooooooooooMMMMoooooMMooooooooooooMM\n"
                "_______88____MMoooooooooMMMMMMMMMMMMMooooooooMMMooooooooMM\n"
                "________88____MMooooooooooooMMMMMMMooooooooooooMMMMMMMMMM\n"
                "_________88___8MMooooooooooooooooooooooooooooooooooMMMMMM\n"
                "__________8___88MMooooooooooooooooooooooMoooMooooooooMM\n"
                "______________888MMooooooooooooooooooMMooooooMMooooooMM\n"
                "_____________88888MMoooooooooooooooMMMooooooomMoooooMM\n"
                "_____________888888MMoooooooooooooMMMoooooooooMMMoooM\n"
                "____________88888888MMoooooooooooMMMoooooooooooMMoooM\n"
                "___________88_8888888MoooooooooMMMooooooooooooooMoooM\n"
                "___________8__888888_MoooooooMMoooooooooooooooooMoooMo\n"
                "______________888888_MooooooMoooooooooooooooooooMoooMM\n"
                "_____________888888__MoooooMooooooooooooooooooooooooMoM\n"
                "_____________888888__MoooooMooooooooo@ooooooooooooooMooM\n"
                "_____________88888___Moooooooooooooo@@oooooooooooooooMooM\n"
                "____________88888___Moooooooooooooo@@@ooooooooooooooooMooM\n"
                "___________88888___Mooooooooooooooo@@ooooooooooooooooooMooM\n"
                "__________88888___Mooooomoooooooooo@ooooooooooMmoooooooMoooM\n"
                "__________8888___MoooooMoooooooooooooooooooooooMMoooooooMoooM\n"
                "_________8888___MoooooMoooooooooooooooooooooooMMMooooooooMoooM\n"
                "________888____MoooooMmooooooooooooooooooooooMMMoooooooooMooooM\n"
                "______8888____MMooooMmoooooooooooooooooooooMMMMooooooooomoomoooM\n"
                "_____888______MoooooMooooooooooooooooooooMMMooooooooooooMoommoooM\n"
                "__8888_______MMoooooooooooooooooooooooooMMooooooooooooomMooMMoooMo\n"
                "_____________MoooooooooooooooooooooooooMooooooooooooooomMooMMoooMm\n"
                "____________MMoooooomoooooooooooooooooooooooooooooooooooMooMMoooMM\n"
                "____________MooooooooMoooooooooooooooooooooooooooooooooooMooMoooMM\n"
                "___________MMoooooooooMoooooooooooooMoooooooooooooooooooooMoMoooMM\n"
                "___________MoooooooooooM88oooooooooMoooooooooooooooooooooooMMooMMM\n"
                "___________Moooooooooooo8888888888MooooooooooooooooooooooooMMooMM\n"
                "___________Mooooooooooooo88888888MoooooooooooooooooooooooooMooMM\n"
                "___________Moooooooooooooo888888MoooooooooooooooooooooooooMooMM\n"
                "___________Mooooooooooooooo88888MoooooooooooooooooooooooooMoMM\n"
                "___________Mooooooooooooooooo88MooooooooooooooooooooooooooMMM\n"
                "___________MoooooooooooooooooooMooooooooooooooooooooooooooMMM\n"
                "___________MMoooooooooooooooooMooooooooooooooooooooooooooMMM\n"
                "____________MoooooooooooooooooMooooooooooooooooooooooooooMMM\n"
                "____________MMoooooooooooooooMooooooooooooooooooooooooooMMM\n"
                "_____________MoooooooooooooooMoooooooooooooooooooooooooMMM\n"
                "_____________MMoooooooooooooMoooooooooooooooooooooooooMMM\n"
                "______________MoooooooooooooMooooooooooooooooooooooooMMM\n"
                "______________MMoooooooooooMooooooooooooooooooooooooMMM\n"
                "_______________MoooooooooooMoooooooooooooooooooooooMMM\n"
                "_______________MMoooooooooMoooooooooooooooooooooooMMM\n"
                "________________MoooooooooMooooooooooooooooooooooMMM\n"
                "________________MMoooooooMooooooooooooooooooooooMMM\n"
                "_________________MMooooooMoooooooooooooooooooooMMM\n"
                "_________________MMoooooMoooooooooooooooooooooMMM\n"
                "__________________MMooooMooooooooooooooooooooMMM\n"
                "__________________MMoooMooooooooooooooooooooMMM\n"
                "___________________MMooMoooooooooooooooooooMMM\n"
                "___________________MMoMoooooooooooooooooooMMM\n"
                "____________________MMMooooooooooooooooooMMM\n"
                "____________________MMooooooooooooooooooMMM\n"
                "_____________________MoooooooooooooooooMMM\n"
                "____________________MMooooooooooooooooMMM\n"
                "____________________MMoooooooooooooooMMM\n"
                "____________________MMooooMoooooooooMMMo\n"
                "____________________mMMooooMMoooooooMMMM\n"
                "_____________________MMMoooooooooooMMMoM\n"
                "_____________________mMMoooMoooooooMoMoM\n"
                "______________________MMooMMMMoooooooMoM\n"
                "______________________MMooMMMooooooooMoM\n"
                "______________________mMMooMMooooooooMoM\n"
                "_______________________MMooMMoooooooooMoM\n"
                "_______________________MMooMMooooooooooMom\n"
                "_______________________MMoooMoooooooooooMM\n"
                "_______________________MMoooMoooooooooooMM\n"
                "_______________________MMMoooooooooooooooMo\n"
                "_______________________MMMoooooooooooooooMo\n"
                "_______________________MMMooooooooooooooooM\n"
                "_______________________MMMooooooooooooooooM\n"
                "_______________________MMMooooooooooooooooMm\n"
                "________________________MMooooooooooooooooMM\n"
                "________________________MMMoooooooooooooooMM\n"
                "________________________MMMoooooooooooooooMM\n"
                "________________________MMMoooooooooooooooMM\n"
                "________________________MMMoooooooooooooooMM\n"
                "_________________________MMooooooooooooooMMM\n"
                "_________________________MMMoooooooooooooMM\n"
                "_________________________MMMoooooooooooooMM\n"
                "_________________________MMMooooooooooooMM\n"
                "__________________________MMooooooooooooMM\n"
                "__________________________MMooooooooooooMM\n"
                "__________________________MMoooooooooooMM\n"
                "__________________________MMMooooooooooMM\n"
                "__________________________MMMooooooooooMM\n"
                "___________________________MMoooooooooMM\n"
                "___________________________MMMooooooooMM\n"
                "___________________________MMMooooooooMM\n"
                "____________________________MMooooooooMM\n"
                "____________________________MMMooooooMM\n"
                "____________________________MMMooooooMM\n"
                "_____________________________MMooooooMM\n"
                "_____________________________MMooooooMM\n"
                "______________________________MMoooooMM\n"
                "______________________________MMoooooMMo\n"
                "______________________________MMoooooMoM\n"
                "______________________________MMoooooMoM\n"
                "______________________________oMooooooMo\n"
                "_____________________________MoMoooooooM\n"
                "____________________________MoooMooooooM\n"
                "___________________________MooooMooooooM\n"
                "__________________________MoooooMoooooooM\n"
                "_________________________MooooooMMoooooooM\n"
                "_________________________MoooooooMooooooooM\n"
                "_________________________M;o;ooooMoooooooooM\n"
                "_________________________Momo;oooMooooooooooM\n"
                "_________________________MMomomooMoooooooo;oM\n"
                "__________________________MMomooMMooooooo;o;M\n"
                "___________________________MMooMMMoooooo;omoM\n"
                "___________________________MMMM_MMoooomomoMM\n"
                "__________________________________MMoooomoMM\n"
                "___________________________________MMooooMM\n"
                "_____________________________________MMMMM\n"
                ;
        } else {
            std::cout<<
                ".................0..l..0.................\n"
                "..............0.....l.....0..............\n"
                ".............0.............0.............\n"
                "............0...............0............\n"
                "............0...............0............\n"
                ".............0.0.0.0.0.0.0.0.............\n"
                "..............0...........0..............\n"
                "..............0...........0..............\n"
                "..............0...........0..............\n"
                "..............0...........0..............\n"
                "..............0...........0..............\n"
                "..............0...........0..............\n"
                "..............0...........0..............\n"
                "..............0...........0..............\n"
                "..............0...........0..............\n"
                "..............0...........0..............\n"
                "..............0...........0..............\n"
                "..............0...........0..............\n"
                "..............0...........0..............\n"
                "......0..0....0...........0....0..0......\n"
                "...0........0.0...........0.0........0...\n"
                ".0...........00...........00...........0.\n"
                "0.......................................0\n"
                "0.......................................0\n"
                "0.......................................0\n"
                ".0.....................................0.\n"
                ;
        } //if

        pic++;
        #endif //OPTION_ENABLE_MOO_DEFINED

    } //moo
}; //pann


#ifdef OPTION_BUILD_PYTHON_BINDINGS_DEFINED

#include "Includes/Python.h"

namespace pann {
namespace python {
    void export_Moo()
    {
        using namespace boost::python;

        def("moo", moo);
    }
}; //python
}; //pann

#endif //OPTION_BUILD_PYTHON_BINDINGS_DEFINED

