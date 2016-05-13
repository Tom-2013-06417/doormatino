class CreateCounts < ActiveRecord::Migration
  def change
    create_table :counts do |t|
      t.integer :value

      t.timestamps null: true
    end
  end
end
