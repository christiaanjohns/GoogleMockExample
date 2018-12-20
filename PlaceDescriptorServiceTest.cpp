#include <gmock/gmock.h>

#include <iostream>
#include <string>
#include "PlaceDescriptionService.h"
#include "Http.h"

using namespace std;
using namespace testing;

//Fixture class for testing purposes
class APlaceDescriptionService : public Test
{
public:
    static const string ValidLatitude;
    static const string ValidLongitude;
};

const string APlaceDescriptionService::ValidLatitude("38.005");
const string APlaceDescriptionService::ValidLongitude("-104.44");

//Stub Class: returns hard coded value
class HttpStub: public Http
{
public:
    // MOCK_METHOD0(,): 0 for 0 input params
    //      firstParam: method name
    //      secondParam: method type
    MOCK_METHOD0(initialize, void());
    MOCK_CONST_METHOD1(get, string(const string&));
};

TEST_F(APlaceDescriptionService, RetrunDescriptionForValidLocation)
{
    HttpStub httpStub;  //test double
    string urlStart(
            "http://open.mapquestapi.com/nominatim/v1/reverse?format=json&");
    string expectedURL(urlStart +
                       "lat=" + APlaceDescriptionService::ValidLatitude + "&" +
                       "lon=" + APlaceDescriptionService::ValidLongitude);
    EXPECT_CALL(httpStub, get(expectedURL));

    PlaceDescriptionService service(&httpStub);

    service.summaryDescription(ValidLatitude, ValidLongitude);
}

//Stub Class: returns hard coded value
// Mock class to return info without having to connect to service, for testing purposes.
//class HttpStub: public Http
//{
//public:
//    std::string returnResponse;
//    std::string expectedURL;
//    void initialize() override {}
//
//    std::string get(const std::string& url)const override
//    {
//        verify(url);
//        return returnResponse;//
//    }
//
//    void verify(const std::string& url)const
//    {
//        ASSERT_THAT(url, EndsWith(expectedURL));
//    }
//};