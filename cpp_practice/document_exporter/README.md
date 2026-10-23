# Document Exporter

Export documents as text or CSV through `DocumentExporter`.
C++20, standard library only, one thread. Modify only `after/main.cpp`.

## Task

Implement `CsvExporter::Export`, `MakeExporter`, and `ExportBatch`.
Review existing code against these rules:

- Empty titles are invalid (`std::invalid_argument`); empty bodies are valid.
  Preserve input text and do not modify documents. Exporters remain reusable.
- Text: exactly `title + "\n" + body + "\n"`.
- CSV: always quote both fields, separate with a comma, double internal quotes,
  and end each record with `\n`. Preserve commas/newlines; no header.
  Example: `"Note","He said ""hello"""` followed by a newline.
- `MakeExporter("text")` / `MakeExporter("csv")`: return a non-null owning
  `std::unique_ptr<DocumentExporter>` of the requested type. Other names,
  including different casing, throw `std::invalid_argument`.
- `ExportBatch`: borrow the exporter, process documents through its interface in
  input order, concatenate successful output, and count successes in `exported`.
  Record zero-based indices of documents throwing `std::invalid_argument` in
  `rejected_indices` and continue. Propagate other exceptions unchanged.
- Empty batches return empty content, zero successes, and no rejected indices.
  Returned strings own their data; batch export does not modify the input.

Check both formats, empty/invalid input, quotes, commas, newlines, unknown
formats, repeated calls, and continuation after rejected documents.

## Build and run

From `after/`:

```sh
clang++ -std=c++20 -Wall -Wextra -Wpedantic -g -O1 \
  -fsanitize=address,undefined -fno-omit-frame-pointer \
  main.cpp -o /tmp/document_exporter.out && /tmp/document_exporter.out
```
