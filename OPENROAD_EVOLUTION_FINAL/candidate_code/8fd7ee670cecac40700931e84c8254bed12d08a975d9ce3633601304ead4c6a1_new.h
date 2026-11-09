// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.30596451;
  double density_weight = 0.28899530;
  double prefix_weight = 0.10117712;
  double neighborhood_weight = 0.27825873;
  double late_weight = 0.09404856;
  double critical_weight = 0.39861086;
  unsigned budget = 36;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
