open Jest;

describe("Subject", () =>
  testAsync("make", finish => {
    let s = Subject.make();
    Subject.asStream(s)
    |. Observable.subscribe(x =>
         Expect.expect(x) |> Expect.toEqual(10) |> finish
       )
    |. ignore;
    s |. Subject.next(10) |. Subject.complete;
  })
);
