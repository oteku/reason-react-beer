let container_style =
  ReactDOMRe.Style.make(~display="flex", ~flexDirection="column", ());

let header_style =
  ReactDOMRe.Style.make(
    ~alignItems="center",
    ~display="flex",
    ~flexDirection="row",
    ~justifyContent="space-around",
    ~paddingLeft="20px",
    ~paddingRight="20px",
    ~height="100%",
    ~backgroundColor="rgb(36, 41, 48)",
    (),
  );

let section_style =
  ReactDOMRe.Style.make(
    ~alignItems="center",
    ~display="flex",
    ~flexDirection="column",
    ~justifyContent="center",
    ~height="30rem",
    ~fontSize="1.5rem",
    ~fontWeight="200",
    (),
  );

let logo_style = ReactDOMRe.Style.make(~height="200px", ());
let circle_style =
  ReactDOMRe.Style.make(~borderRadius="50%", ~cursor="pointer", ());
let headline_h3_style =
  ReactDOMRe.Style.make(
    ~color="rgb(236, 236, 236)",
    ~flexBasis="430px",
    ~fontSize="2.5rem",
    ~fontWeight="400",
    ~letterSpacing="1px",
    ~lineHeight="4rem",
    ~width="50%",
    ~textAlign="left",
    ~alignItems="flex-start",
    (),
  );

let headline_span_style =
  ReactDOMRe.Style.make(
    ~borderBottomStyle="solid",
    ~borderBottomWidth="3px",
    ~borderBottomColor="rgb(246, 197, 78)",
    ~display="inline",
    (),
  );

[@react.component]
let make = () => {
  let intro = [%raw {|' des amoureux.ses de houblon ⚛️'|}];
  let icn_beer = [%raw {|'🍺'|}];
  <div style=container_style>
    <div style=header_style>
      <img
        src="https://reactbeerlille.org/img/react-beer-lille.png"
        alt="react beer logo"
        style=logo_style
      />
      <h3 style=headline_h3_style>
        <span style=headline_span_style>
          {React.string("Bienvenue au meetup React lillois")}
          intro
          icn_beer
        </span>
      </h3>
    </div>
    <div style=section_style>
      <a onClick={_ => ReasonReactRouter.push("/brewries")}>
        <img
          src="https://66.media.tumblr.com/avatar_22086c29f760_96.pnj"
          alt="untappd logo"
          style=circle_style
        />
      </a>
      <span> {React.string("Parcourir les brasseries avec Untappd")} </span>
    </div>
  </div>;
};