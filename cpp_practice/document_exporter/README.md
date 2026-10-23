# Document Exporter

A backend service exports documents in different formats. Callers use one interface;
the selected exporter determines the representation.

This is an in-memory, single-threaded exercise: C++20, standard library only.
There are no files, network calls, or threads.

## Work

Review the existing implementation against the contract below and complete:

- `CsvExporter::Export`.
- `MakeExporter`.
- `ExportBatch`.

These three functions are deliberately incomplete. Other starter behavior may
also disagree with the contract. Work only in `after/main.cpp`; preserve `before/`.
Do not implement a separate batch algorithm for each format.

## Contract

### Documents and exporters

- A document owns its title and body. An empty title is invalid; an empty body is valid.
- Do not trim whitespace or otherwise change input text.
- Both exporters implement `DocumentExporter` and support calls through its interface.
- `Export` returns an owning string and does not modify the document.
- An invalid document causes `std::invalid_argument`.
- Exporters remain usable for subsequent calls after an invalid document.

### Plain text

Output is exactly `title + "\n" + body + "\n"`.

For `{"Status", "Ready"}`, the result is:

```text
Status
Ready
```

An empty body still contributes its final newline.

### CSV

CSV is a table representation: each document contributes two fields, title and body.

- Always enclose each field in double quotes.
- Separate the two fields with one comma.
- Represent a double quote inside a field as two double quotes.
- Preserve commas and newline characters inside quoted fields.
- End each record with `\n`; do not add a header.

For `{"Note", "He said \"hello\""}`, the result is:

```csv
"Note","He said ""hello"""
```

For `{"Empty body", ""}`, the result is:

```csv
"Empty body",""
```

### Factory and ownership

- `MakeExporter("text")` returns an owning `std::unique_ptr<DocumentExporter>`
  containing a plain text exporter.
- `MakeExporter("csv")` returns an owning pointer containing a CSV exporter.
- Any other name causes `std::invalid_argument`; names are case-sensitive.
- Do not return null for a recognized format.
- The caller owns the exporter; batch export only borrows it.

### Batch export

- Process documents in their original order using the supplied exporter.
- Concatenate successful outputs into `content` without additional separators.
- Count successful documents in `exported`.
- For a document that raises `std::invalid_argument`, record its zero-based index
  in `rejected_indices` and continue with the following document.
- Propagate other exception types.
- An empty batch returns empty content, zero exported documents, and no rejected indices.
- Do not modify the documents or take ownership of the exporter.

The completed starter example should print:

```text
"Status","Ready"
"Note","He said ""hello"""
"Empty body",""
Exported: 3
Rejected: 1
```

Its rejected indices should be `{1}`.

## Checks to add

Keep `main` short. Cover both formats through the common interface, empty input,
invalid documents before valid ones, empty bodies, quotes, commas, and embedded
newlines. Also check an unknown format and repeated calls on the same exporter.

## Build and run

From `after/`:

```sh
clang++ -std=c++20 -Wall -Wextra -Wpedantic -g -O1 \
  -fsanitize=address,undefined -fno-omit-frame-pointer \
  main.cpp -o /tmp/document_exporter.out && /tmp/document_exporter.out
```
