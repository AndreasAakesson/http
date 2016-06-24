// This file is a part of the IncludeOS unikernel - www.includeos.org
//
// Copyright 2015-2016 Oslo and Akershus University College of Applied Sciences
// and Alfred Bratterud
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef SERVICE_ROUTE_TABLE_HPP
#define SERVICE_ROUTE_TABLE_HPP


static http::Router init_routes() {
  using namespace std;
  using namespace http;
  //--------------------------------------------------------------------
  HeaderSet service_headers {
    {header_fields::Response::Server, "IncludeOS/v0.7.0"},
    {header_fields::Entity::Content_Type, "text/html; charset=utf-8"},
    {header_fields::Response::Connection, "close"}
  };
  //--------------------------------------------------------------------
  Router routes;
  //--------------------------------------------------------------------
  routes.on_get("/"s, [&service_headers](const auto&, auto& res){
    (res << service_headers).add_header("Date"s, http::time::now())
                            .add_body("<h1>WELCOME TO IncludeOS</h1>"s);
  })
  //--------------------------------------------------------------------
  .on_get("/listing.html"s, [&service_headers](const auto&, auto& res){
    (res << service_headers).add_header("Date"s, http::time::now())
                            .add_body("<h1>IncludeOS Main Developers</h1>"
                                      "<ul>"
                                      "<li>Alfred Bratterud</li>"
                                      "<li>Alf-Andre Walla</li>"
                                      "<li>Andreas Åkesson</li>"
                                      "<li>Rico Antonio Felix</li>"
                                      "</ul>"s);
  })
  //--------------------------------------------------------------------
  .on_post("/"s, [&service_headers](const auto&, auto& res){
    (res << service_headers).add_header("Date"s, http::time::now())
                            .add_body("NO POSTING TODAY!!!"s);
  })
  //--------------------------------------------------------------------
  .on_head("/Unikernels.pdf"s, [](const auto&, auto& res){
    res.add_header(header_fields::Response::Server, "IncludeOS/v0.7.0"s)
       .add_header("Date"s, http::time::now())
       .add_header(header_fields::Response::Connection, "close"s)
       .add_header("X-File-Size"s, "6.8MB"s);
  });
  //--------------------------------------------------------------------
  return routes;
}

#endif //< SERVICE_ROUTE_TABLE_HPP
