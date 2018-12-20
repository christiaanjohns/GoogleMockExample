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
// Mock class to return info without having to connect to service, for testing purposes.
class HttpStub: public Http
{
    void initialize() override {}
    std::string get(const std::string& url)const override
    {
        verify(url);
        return R"({ "address": {
            "road":"Drury Ln",
            "city":"Fountain",
            "state":"CO",
            "country":"US"} } )";
    }

    void verify(const std::string& url)const
    {
        string urlStart(
                "http://open.mapquestapi.com/nominatim/v1/reverse?format=json&");
        string expected(urlStart +
                "lat=" + APlaceDescriptionService::ValidLatitude + "&" +
                "lon=" + APlaceDescriptionService::ValidLongitude);
        ASSERT_THAT(url, EndsWith(expected));
    }
};

TEST_F(APlaceDescriptionService, RetrunDescriptionForValidLocation)
{
    HttpStub httpStub;  //test double
    PlaceDescriptionService service(&httpStub);

    auto description = service.summaryDescription(ValidLatitude, ValidLongitude);
    ASSERT_THAT(description, Eq("Drury Ln, Fountain, CO, US"));
}