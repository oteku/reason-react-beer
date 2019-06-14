type resp('a) = {response: 'a}
and resp_breweries = resp(ubreweries_resp)
and resp_beers = resp(ubeers_resp)
and ubreweries_resp = {
  brewery: ubreweries,
  found: int,
}
and uitems('a) = {
  count: int,
  items: array('a),
}
and ubreweries = uitems(ubrewery)
and ubeers = uitems(ubeer)
and ubrewery = {brewery: ubrewery_details}
and ubrewery_details = {
  brewery_name: string,
  brewery_label: string,
  country_name: string,
}
and ubeers_resp = {
  beers: ubeers,
  found: int,
}
and ubeer = {
  beer: ubeer_details,
  brewery: ubrewery_details,
}
and ubeer_details = {
  beer_name: string,
  beer_label: string,
  beer_description: string,
  beer_abv: float,
  beer_style: string,
};

module Decode = {
  let ubrewery_details = json =>
    Json.Decode.{
      brewery_name: json |> field("brewery_name", string),
      brewery_label: json |> field("brewery_label", string),
      country_name: json |> field("country_name", string),
    };

  let ubeer_details = json =>
    Json.Decode.{
      beer_name: json |> field("beer_name", string),
      beer_label: json |> field("beer_label", string),
      beer_description: json |> field("beer_description", string),
      beer_abv: json |> field("beer_abv", float),
      beer_style: json |> field("beer_style", string),
    };

  let ubrewery = json =>
    Json.Decode.{brewery: json |> field("brewery", ubrewery_details)};

  let ubeer = json =>
    Json.Decode.{
      beer: json |> field("beer", ubeer_details),
      brewery: json |> field("brewery", ubrewery_details),
    };

  let uitems = (decode_items, json) =>
    Json.Decode.{
      count: json |> field("count", int),
      items: json |> field("items", array(decode_items)),
    };
  let ubreweries = uitems(ubrewery);
  let ubeers = uitems(ubeer);
  let ubreweries_resp = json =>
    Json.Decode.{
      brewery: json |> field("brewery", ubreweries),
      found: json |> field("found", int),
    };

  let ubeers_resp = json =>
    Json.Decode.{
      beers: json |> field("beers", ubeers),
      found: json |> field("found", int),
    };

  let resp = (decode_resp, json) =>
    Json.Decode.{response: json |> field("response", decode_resp)};
  let resp_breweries = resp(ubreweries_resp);
  let resp_beers = resp(ubeers_resp);
};