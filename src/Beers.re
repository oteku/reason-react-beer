let section_style = ReactDOMRe.Style.make(~display="inherit", ());
let header_style =
  ReactDOMRe.Style.make(
    ~height="50px",
    ~backgroundColor="rgb(246, 197, 78)",
    ~fontSize="1.5rem",
    ~fontWeight="500",
    ~display="flex",
    ~flexDirection="row",
    ~alignContent="center",
    ~alignItems="center",
    ~justifyContent="center",
    (),
  );

let list_style =
  ReactDOMRe.Style.make(
    ~display="flex",
    ~flexDirection="row",
    ~flexWrap="wrap",
    ~alignItems="stetch",
    ~justifyContent="center",
    (),
  );
let item_style =
  ReactDOMRe.Style.make(
    ~display="inherit",
    ~flexDirection="column",
    ~width="30%",
    ~flexWrap="wrap",
    ~alignContent="center",
    ~alignItems="center",
    ~justifyContent="space-around",
    ~padding="20px",
    ~margin="3px",
    ~borderWidth="3px",
    ~borderStyle="solid",
    ~borderColor="rgba(246, 197, 78, 0.2)",
    (),
  );
let logo_style =
  ReactDOMRe.Style.make(~width="6rem", ~paddingBottom="5px", ());
let link_style =
  ReactDOMRe.Style.make(
    ~cursor="pointer",
    ~fontSize="2.5rem",
    ~fontWeight="200",
    (),
  );
let link_nav_style =
  ReactDOMRe.Style.make(
    ~cursor="pointer",
    ~fontSize="1.5rem",
    ~fontWeight="100",
    (),
  );
let nav_style =
  ReactDOMRe.Style.make(
    ~display="flex",
    ~flexDirection="row",
    ~alignContent="center",
    ~alignItems="center",
    ~justifyContent="center",
    (),
  );

[@react.component]
let make = (~query: string) => {
  let init_beers: array(Model.ubeer) = [||];
  let (beers, set_beers) = React.useState(() => init_beers);

  React.useEffect1(
    () => {
      let _ =
        Js.Promise.(
          Api.Untappd.get_beers(query, 0)
          |> then_((response: Model.ubeers) => {
               set_beers(_ => response.items);
               resolve();
             })
        );
      Some(() => ());
    },
    [|query|],
  );

  let icn_need = [%raw {|'🤤'|}];
  let icn_0 = [%raw {|'🤨'|}];
  let icn_5 = [%raw {|'😊'|}];
  let icn_8 = [%raw {|'🤪'|}];
  let icn_10 = [%raw {|'😵'|}];
  let beers_list =
    ReactDOMRe.createDOMElementVariadic(
      "ul",
      ~props=ReactDOMRe.domProps(~style=list_style, ()),
      Array.map(
        (b: Model.ubeer) =>
          ReactDOMRe.createDOMElementVariadic(
            "li",
            ~props=ReactDOMRe.domProps(~style=item_style, ()),
            [|
              <img
                style=logo_style
                src={b.beer.beer_label}
                title={b.beer.beer_description}
              />,
              <span>
                {React.string(
                   b.beer.beer_name ++ " - " ++ b.beer.beer_style ++ " ",
                 )}
                {b.beer.beer_abv > 10.
                   ? icn_10
                   : b.beer.beer_abv > 8.
                       ? icn_8 : b.beer.beer_abv > 5. ? icn_5 : icn_0}
              </span>,
              <a
                style=link_style
                href={
                  "https://www.saveur-biere.com/fr/search-result/"
                  ++ Js.Global.encodeURI(b.beer.beer_name)
                }>
                icn_need
              </a>,
            |],
          ),
        beers,
      ),
    );

  <div style=section_style>
    <div style=header_style>
      <span>
        {Array.length(beers) |> string_of_int |> React.string}
        {React.string({js| Bières - |js} ++ Js.Global.decodeURI(query))}
      </span>
    </div>
    beers_list
  </div>;
};