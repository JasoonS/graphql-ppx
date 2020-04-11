[@ocaml.ppx.context
  {
    tool_name: "migrate_driver",
    include_dirs: [],
    load_path: [],
    open_modules: [],
    for_package: None,
    debug: false,
    use_threads: false,
    use_vmthreads: false,
    recursive_types: false,
    principal: false,
    transparent_modules: false,
    unboxed_types: false,
    unsafe_string: false,
    cookies: [],
  }
];
module MyQuery = {
  module Raw = {
    type t = {customScalarField: t_customScalarField}
    and t_customScalarField = {
      nullable: Js.Nullable.t(Js.Json.t),
      nonNullable: Js.Json.t,
    };
  };
  let query = "query ($opt: CustomScalar, $req: CustomScalar!)  {\ncustomScalarField(argOptional: $opt, argRequired: $req)  {\nnullable  \nnonNullable  \n}\n\n}\n";
  type t = {customScalarField: t_customScalarField}
  and t_customScalarField = {
    nullable: option(Js.Json.t),
    nonNullable: Js.Json.t,
  };
  type t_variables = {
    opt: option(Js.Json.t),
    req: Js.Json.t,
  };
  let parse: Js.Json.t => t =
    (value) => (
      {

        customScalarField: {
          let value =
            Js.Dict.unsafeGet(Obj.magic(value), "customScalarField");
          (
            {

              nullable: {
                let value = Js.Dict.unsafeGet(Obj.magic(value), "nullable");

                switch (Js.toOption(Obj.magic(value): Js.Nullable.t('a))) {
                | Some(_) => Some(value)
                | None => None
                };
              },

              nonNullable: {
                let value =
                  Js.Dict.unsafeGet(Obj.magic(value), "nonNullable");
                value;
              },
            }: t_customScalarField
          );
        },
      }: t
    );
  let serializeVariables: t_variables => Js.Json.t =
    inp =>
      [|
        (
          "opt",
          (
            a =>
              switch (a) {
              | None => None
              | Some(b) => (a => Some(a))(b)
              }
          )(
            inp.opt,
          ),
        ),
        ("req", (a => Some(a))(inp.req)),
      |]
      |> Js.Array.filter(
           fun
           | (_, None) => false
           | (_, Some(_)) => true,
         )
      |> Js.Array.map(
           fun
           | (k, Some(v)) => (k, v)
           | (k, None) => (k, Js.Json.null),
         )
      |> Js.Dict.fromArray
      |> Js.Json.object_;
  let makeVar = (~f, ~opt=?, ~req, ()) =>
    f(
      serializeVariables(
        {

          opt,

          req,
        }: t_variables,
      ),
    );
  let definition = (parse, query, makeVar);
  let makeVariables = makeVar(~f=f => f);
};