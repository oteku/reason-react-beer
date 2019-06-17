# ReasonReact Beer

This is a ReasonReact sample project made for [React Beer Lille #3](https://www.meetup.com/fr-FR/ReactBeerLille/events/262028719/)

## Run Project

```sh
npm install
npm run build
npm run webpack
```

## Configure the project

- Register an app on Untappd for an api key https://untappd.com/api/dashboard
- Create a `.env` file with your keys

```sh
CLIENT_ID=MY_APP_CLIENT_ID
CLIENT_SECRET=MY_APP_CLIENT_SECRET
```

## Run Project with Server

To run with the webpack development server run `npm run dev` and view in the browser at http://localhost:8000. Running in this environment provides hot reloading and support for routing; just edit and save the file and the browser will automatically refresh.

To use a port other than 8000 set the `PORT` environment variable (`PORT=8080 npm run server`).

## Build for Production

```sh
npm run clean
npm run build
npm run webpack:production
```

This will replace the development artifact `build/Index.js` for an optimized version as well as copy `src/index.html` into `build/`. You can then deploy the contents of the `build` directory (`index.html` and `Index.js`).

If you make use of routing (via `ReasonReact.Router` or similar logic) ensure that server-side routing handles your routes or that 404's are directed back to `index.html` (which is how the dev server is set up).

**To enable dead code elimination**, change `bsconfig.json`'s `package-specs` `module` from `"commonjs"` to `"es6"`. Then re-run the above 2 commands. This will allow Webpack to remove unused code.
