#!/bin/bash

for file in *; do
    # Skip if not a regular file
    [ ! -f "$file" ] && continue
    
    # Extract the leading numbers before the first hyphen
    newname=$(echo "$file" | sed -E 's/^([0-9]+)-.*(\..*)$/\1\2/')
    
    # If the rename would be effective (i.e., the filename matches our pattern)
    if [[ "$file" != "$newname" ]]; then
        # Check if the new filename already exists
        if [ -e "$newname" ]; then
            echo "Warning: $newname already exists - skipping $file"
        else
            mv -v "$file" "$newname"
        fi
    fi
done
