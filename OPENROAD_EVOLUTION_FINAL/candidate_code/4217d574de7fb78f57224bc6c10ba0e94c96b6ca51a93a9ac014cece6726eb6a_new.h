// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.56573646;
  double density_weight = 0.42867761;
  double prefix_weight = 0.40471566;
  double neighborhood_weight = 0.28751489;
  double late_weight = 0.27661848;
  double critical_weight = 0.22401478;
  unsigned budget = 32;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
