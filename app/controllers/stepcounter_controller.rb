class StepcounterController < ApplicationController
	
	def init
	end


	def index
		step = Count.all
      	
      	if not step.any?
			a = Count.new(value: 0)
			a.save
		end

		@var = Count.first
	end


	def update
		@temp = Count.first.value
		Count.update(1, :value => @temp+params[:steps][:value])
		render nothing: true
	end


	def reset
		Count.update(1, :value => 0)
		redirect_to "/stepcounter/index"
	end


	protected

	def json_request?
		request.format.json?
	end

	
	private

	def stepcounter_params
	  params.require(:steps).permit(:value)
	end

end
