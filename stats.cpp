#include "stats.h"

Stats::Stats() {
    methods["GET"] = 0;
    methods["PUT"] = 0;
    methods["POST"] = 0;
    methods["DELETE"] = 0;
    methods["UNKNOWN"] = 0;

    uris["/"] = 0;
    uris["/order"] = 0;
    uris["/product"] = 0;
    uris["/basket"] = 0;
    uris["/help"] = 0;
    uris["unknown"] = 0;
}

void Stats::AddMethod(string_view method) {
    if (
        method == "GET"  || 
        method == "PUT"  || 
        method == "POST" || 
        method == "DELETE") {
        ++methods[method];
    }
    else {
        ++methods["UNKNOWN"];
    }
}

void Stats::AddUri(string_view uri) {
    if (
        uri == "/" ||
        uri == "/order" ||
        uri == "/product" ||
        uri == "/basket" ||
        uri == "/help") {
        ++uris[uri];
    }
    else {
        ++uris["unknown"];
    }
}

const map<string_view, int>& Stats::GetMethodStats() const {
    return methods;
}

const map<string_view, int>& Stats::GetUriStats() const {
    return uris;
}

HttpRequest ParseRequest(string_view line) {
    HttpRequest res;
    
    while (line[0] == ' ') {
        line.remove_prefix(1);
    }

    size_t pos = line.find(' ');
    res.method = line.substr(0, pos);
    line.remove_prefix(pos + 1);
    pos = line.find(' ');
    res.uri = line.substr(0, pos);
    line.remove_prefix(pos + 1);
    res.protocol = line.substr(0, line.npos);

    return res;
}