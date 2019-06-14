[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  switch (url.path, url.hash, url.search) {
  | ([], _, _) => <Welcome />
  | (["brewries"], offset, _) =>
    <Breweries
      query="france"
      offset={
        switch (int_of_string(offset)) {
        | offset_int => offset_int
        | exception _ => 0
        }
      }
    />
  | (["beers"], _, qs) =>
    <Beers query={Array.get(Js.String.split("=", qs), 1)} />
  | _ => <div> {React.string("404")} </div>
  };
};