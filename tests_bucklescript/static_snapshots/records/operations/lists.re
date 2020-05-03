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
    type t_lists = {
      nullableOfNullable: Js.Nullable.t(array(Js.Nullable.t(string))),
      nullableOfNonNullable: Js.Nullable.t(array(string)),
      nonNullableOfNullable: array(Js.Nullable.t(string)),
      nonNullableOfNonNullable: array(string),
    };
    type t = {lists: t_lists};
  };
  let query = "query   {\nlists  {\nnullableOfNullable  \nnullableOfNonNullable  \nnonNullableOfNullable  \nnonNullableOfNonNullable  \n}\n\n}\n";
  type t_lists = {
    nullableOfNullable: option(array(option(string))),
    nullableOfNonNullable: option(array(string)),
    nonNullableOfNullable: array(option(string)),
    nonNullableOfNonNullable: array(string),
  };
  type t = {lists: t_lists};
  type operation = t;
  let parse: Raw.t => t =
    (value) => (
      {
        let lists = {
          let value = (value: Raw.t).lists;
          (
            {
              let nonNullableOfNonNullable = {
                let value = (value: Raw.t_lists).nonNullableOfNonNullable;
                value |> Js.Array.map(value => value);
              }
              and nonNullableOfNullable = {
                let value = (value: Raw.t_lists).nonNullableOfNullable;
                value
                |> Js.Array.map(value =>
                     switch (Js.toOption(value)) {
                     | Some(value) => Some(value)
                     | None => None
                     }
                   );
              }
              and nullableOfNonNullable = {
                let value = (value: Raw.t_lists).nullableOfNonNullable;
                switch (Js.toOption(value)) {
                | Some(value) => Some(value |> Js.Array.map(value => value))
                | None => None
                };
              }
              and nullableOfNullable = {
                let value = (value: Raw.t_lists).nullableOfNullable;
                switch (Js.toOption(value)) {
                | Some(value) =>
                  Some(
                    value
                    |> Js.Array.map(value =>
                         switch (Js.toOption(value)) {
                         | Some(value) => Some(value)
                         | None => None
                         }
                       ),
                  )
                | None => None
                };
              };
              {
                nullableOfNullable,
                nullableOfNonNullable,
                nonNullableOfNullable,
                nonNullableOfNonNullable,
              };
            }: t_lists
          );
        };
        {lists: lists};
      }: t
    );
  let serialize: t => Raw.t =
    (value) => (
      {
        let lists = {
          let value = (value: t).lists;
          (
            {
              let nonNullableOfNonNullable = {
                let value = (value: t_lists).nonNullableOfNonNullable;
                value |> Js.Array.map(value => value);
              }
              and nonNullableOfNullable = {
                let value = (value: t_lists).nonNullableOfNullable;
                value
                |> Js.Array.map(value =>
                     switch (value) {
                     | Some(value) => Js.Nullable.return(value)
                     | None => Js.Nullable.null
                     }
                   );
              }
              and nullableOfNonNullable = {
                let value = (value: t_lists).nullableOfNonNullable;
                switch (value) {
                | Some(value) =>
                  Js.Nullable.return(value |> Js.Array.map(value => value))
                | None => Js.Nullable.null
                };
              }
              and nullableOfNullable = {
                let value = (value: t_lists).nullableOfNullable;
                switch (value) {
                | Some(value) =>
                  Js.Nullable.return(
                    value
                    |> Js.Array.map(value =>
                         switch (value) {
                         | Some(value) => Js.Nullable.return(value)
                         | None => Js.Nullable.null
                         }
                       ),
                  )
                | None => Js.Nullable.null
                };
              };
              {
                nullableOfNullable,
                nullableOfNonNullable,
                nonNullableOfNullable,
                nonNullableOfNonNullable,
              };
            }: Raw.t_lists
          );
        };
        {lists: lists};
      }: Raw.t
    );
  let definition = (parse, query, serialize);
};
