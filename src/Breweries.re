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

type state = {
  offset: int,
  count: int,
  breweries: array(Model.ubrewery),
};

type action =
  | Init(state)
  | Next(array(Model.ubrewery))
  | Previous(array(Model.ubrewery));

type navigation =
  | Next
  | Previous;

[@react.component]
let make = (~query: string, ~offset: int) => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | Init(s) => s
        | Next(bws) => {
            ...state,
            offset: Pervasives.min(state.offset + 9, state.count),
            breweries: bws,
          }
        | Previous(bws) => {
            ...state,
            offset: Pervasives.max(state.offset - 9, 0),
            breweries: bws,
          }
        },
      {offset: 0, count: 0, breweries: [||]},
    );

  React.useEffect1(
    () => {
      let _ =
        Js.Promise.(
          Api.Untappd.get_brewries(query, offset)
          |> then_((response: Model.ubreweries) => {
               dispatch(
                 Init({
                   count: response.count,
                   offset: 0,
                   breweries: response.items,
                 }),
               );
               resolve();
             })
        );
      Some(() => ());
    },
    [|query|],
  );

  let icn_cheers = [%raw {|'🍻'|}];
  let powered_by = [%raw {|' propulsé par Untappd'|}];
  let icn_prev = [%raw {|'⬅️'|}];
  let icn_next = [%raw {|'➡️'|}];

  /* Action creator */
  let on_navigate = nav => {
    let _ =
      Js.Promise.(
        switch (nav) {
        | Next =>
          Pervasives.min(state.offset + 9, state.count)
          |> Api.Untappd.get_brewries(query)
          |> then_((response: Model.ubreweries) =>
               dispatch(Next(response.items)) |> resolve
             )
        | Previous =>
          Pervasives.max(state.offset - 9, 0)
          |> Api.Untappd.get_brewries(query)
          |> then_((response: Model.ubreweries) =>
               dispatch(Previous(response.items)) |> resolve
             )
        }
      );
    ();
  };

  let brewries_list =
    ReactDOMRe.createDOMElementVariadic(
      "ul",
      ~props=ReactDOMRe.domProps(~style=list_style, ()),
      Array.map(
        (b: Model.ubrewery) =>
          ReactDOMRe.createDOMElementVariadic(
            "li",
            ~props=ReactDOMRe.domProps(~style=item_style, ()),
            [|
              <img style=logo_style src={b.brewery.brewery_label} />,
              <span>
                {React.string(
                   b.brewery.brewery_name ++ " - " ++ b.brewery.country_name,
                 )}
              </span>,
              <a
                style=link_style
                onClick={_ =>
                  ReasonReactRouter.push(
                    "/beers?q=" ++ Js.Global.encodeURI(b.brewery.brewery_name),
                  )
                }>
                icn_cheers
              </a>,
            |],
          ),
        state.breweries,
      ),
    );

  let nav_bar =
    <div style=nav_style>
      {state.offset > 0
         ? <a style=link_nav_style onClick={_ => on_navigate(Previous)}>
             icn_prev
           </a>
         : React.string("")}
      {React.string(
         " "
         ++ string_of_int(state.offset)
         ++ " / "
         ++ string_of_int(state.count)
         ++ " ",
       )}
      {state.offset < state.count - 9
         ? <a style=link_nav_style onClick={_ => on_navigate(Next)}>
             icn_next
           </a>
         : React.string("")}
    </div>;

  <div style=section_style>
    <div style=header_style>
      <span>
        {React.string("Brasseries de France - ")}
        <i> powered_by </i>
      </span>
    </div>
    nav_bar
    brewries_list
  </div>;
};