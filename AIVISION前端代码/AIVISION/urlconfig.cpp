#include "urlconfig.h"


const QString URLCONFIG::PROTOCOL="http://";
const QString URLCONFIG::IP="192.168.43.30:8080";//67
const QString URLCONFIG::REGISTER_URL=PROTOCOL+IP+"/AIVISION/RegisterAction.action";
const QString URLCONFIG::SEARCH_URL=PROTOCOL+IP+"/AIVISION/feat/FindAction.action";
const QString URLCONFIG::IMAGE_URL=PROTOCOL+IP+"/AIVISION/image/";//example.jpg

URLCONFIG::URLCONFIG()
{

}
