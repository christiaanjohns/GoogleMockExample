#include "PlaceDescriptionService.h"
#include "Http.h"
#include "AddressExtractor.h"
#include "Address.h"
#include <string>

using namespace std;

PlaceDescriptionService::PlaceDescriptionService(Http* http) : http_(http) {}

string PlaceDescriptionService::summaryDescription( const string& latitude, const string& longitude) const
{
    auto request = createGetRequestUrl(latitude, longitude);
    auto response = get(request);
    return summaryDescription(response);
}

std::string PlaceDescriptionService::summaryDescription(const std::string &response) const
{
    AddressExtractor extractor;
    auto address = extractor.addressFrom(response);
    return address.summaryDescription();
}

std::string PlaceDescriptionService::get(const std::string &requestURL) const
{
    return http_->get(requestURL);
}

std::string PlaceDescriptionService::createGetRequestUrl(const std::string &latitude, const std::string &longitude) const
{
    string server{"http://open.mapquestapi.com"};
    string document{"/nominatim/v1/reverse"};
    return server + document + "?" +
           keyValue("format", "json") + "&" +
           keyValue("lat", latitude) + "&" +
           keyValue("lon", longitude);
}

std::string PlaceDescriptionService::keyValue(const std::string &key, const std::string &value) const
{
    return key + "=" + value;
}

