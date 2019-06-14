module Untappd = {
  [@bs.val] external client_id: string = "process.env.CLIENT_ID";
  [@bs.val] external client_secret: string = "process.env.CLIENT_SECRET";
  let api_uri = method_name =>
    "https://api.untappd.com/v4/"
    ++ method_name
    ++ "?client_id="
    ++ client_id
    ++ "&client_secret="
    ++ client_secret;

  let brewery_search = (query, offset, limit) =>
    api_uri("search/brewery")
    ++ "&q="
    ++ query
    ++ "&limit="
    ++ limit
    ++ "&offset="
    ++ offset;

  let brewery_search_by_9 = (query, offset) =>
    "9" |> brewery_search(query, offset);

  let get_brewries = (query, offset) => {
    Js.Promise.(
      Fetch.fetch(brewery_search_by_9(query, string_of_int(offset)))
      |> then_(Fetch.Response.json)
      |> then_(json => Model.Decode.resp_breweries(json) |> resolve)
      |> then_((bws_resp: Model.resp_breweries) => {
           let bws: Model.ubreweries = {
             count: bws_resp.response.found,
             items: bws_resp.response.brewery.items,
           };
           resolve(bws);
         })
    );
  };

  let beer_search = (query, offset, limit) =>
    api_uri("search/beer")
    ++ "&q="
    ++ query
    ++ "&limit="
    ++ limit
    ++ "&offset="
    ++ offset;

  let beer_search_by_50 = (query, offset) =>
    "50" |> beer_search(query, offset);

  let get_beers = (query, offset) => {
    Js.Promise.(
      Fetch.fetch(beer_search_by_50(query, string_of_int(offset)))
      |> then_(Fetch.Response.json)
      |> then_(json => Model.Decode.resp_beers(json) |> resolve)
      |> then_((brs_resp: Model.resp_beers) => {
           let brs: Model.ubeers = {
             count: brs_resp.response.found,
             items: brs_resp.response.beers.items,
           };
           Js.log("mabitea");
           resolve(brs);
         })
      |> catch(err => {
           Js.log2("Failure!!", err);
           let brs: Model.ubeers = {count: 0, items: [||]};
           Js.Promise.resolve(brs);
         })
    );
  };
};